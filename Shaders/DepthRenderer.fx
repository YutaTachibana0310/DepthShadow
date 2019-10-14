//=====================================
//
// DepthRenderer.fx
// 機能:Z値レンダリングシェーダ
// Author:GP12B332 21 立花雄太
//
//=====================================

/**************************************
グローバル変数
***************************************/
float4x4 mtxWorld;				//ワールド行列
float4x4 mtxView;				//ビュー行列
float4x4 mtxProjection;			//プロジェクション行列
float4x4 mtxLightView;			//ライトビュー変換行列
float4x4 mtxLightProjection;	//ライト射影変換行列
float3 lightDir;

texture depthMap;				//深度マップ

/**************************************
テクスチャサンプラ
***************************************/
sampler depthMapSampler = sampler_state
{
	texture = (depthMap);
	AddressU = CLAMP;
	AddressV = CLAMP;
	AddressW = CLAMP;
	MIPFILTER = LINEAR;
	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
};

/**************************************
頂点シェーダ出力構造体
***************************************/
struct DepthMapOutput
{
	float4 pos : POSITION;
	float4 shadowMapTex : TEXCOORD0;
};

/**************************************
深度マップ作成頂点シェーダ
***************************************/
DepthMapOutput VS_DepthMap(float4 pos : POSITION)
{
	DepthMapOutput Out = (DepthMapOutput)0;

	//ワールドビュープロジェクション変換
	Out.pos = mul(pos, mtxWorld);
	Out.pos = mul(Out.pos, mtxLightView);
	Out.pos = mul(Out.pos, mtxLightProjection);
	
	//テクスチャ座標を頂点に合わせる
	Out.shadowMapTex = Out.pos;

	return Out;
}

/**************************************
深度マップ作成ピクセルシェーダ
***************************************/
float4 PS_DepthMap(float4 shadowMapTex : TEXCOORD0) : COLOR0
{
	//Z値算出
	float4 color = shadowMapTex.z / shadowMapTex.w;
	color.a = 1.0f;
	return color;
}

/**************************************
深度バッファシャドウ頂点シェーダ出力構造体
***************************************/
struct DepthShadowOutput
{
	float4 pos : POSITION;
	float4 zCalcTex : COLOR1;
	float4 color : COLOR0;
};

/**************************************
深度バッファシャドウ頂点シェーダ
***************************************/
DepthShadowOutput VS_DepthShadow(
	float4 pos : POSITION,
	float3 normal : NORMAL)
{
	DepthShadowOutput Out = (DepthShadowOutput)0;

	//カメラの目線によるWVP変換
	Out.pos = mul(pos, mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);

	//ライトの目線によるWVP変換
	Out.zCalcTex = mul(pos, mtxWorld);
	Out.zCalcTex = mul(Out.zCalcTex, mtxLightView);
	Out.zCalcTex = mul(Out.zCalcTex, mtxLightProjection);

	//カラーを計算
	float3 N = normalize(mul(normal, mtxWorld));
	float lightDot = max(0.0f, dot(N, -lightDir));
	Out.color = float4(0.0f, 0.5f, 1.0f, 1.0f) * lightDot;
	Out.color.w = 1.0f;

	return Out;
}

/**************************************
深度バッファシャドウピクセルシェーダ
***************************************/
float4 PS_DepthShadow(
	float4 color : COLOR0,
	float4 zCalcTex : COLOR1) : COLOR
{
	//ライト目線によるZ値の再算出
	float zValue = zCalcTex.z / zCalcTex.w;

	//射影空間のXY座標をテクスチャ座標に変換
	float2 transTexCoord;
	transTexCoord.x = (1.0f + zCalcTex.x / zCalcTex.w) * 0.5f;
	transTexCoord.y = (1.0f - zCalcTex.y / zCalcTex.w) * 0.5f;

	//リアルZ値抽出
	float realZ = tex2D(depthMapSampler, transTexCoord).x;

	if (zValue > realZ + 0.005f)
	{
		color.rgb = float3(1.0f, 1.0f, 1.0f) -  color.rgb;
		//color.rgb = color.rgb * 0.5f;
	}

	return color;
}

/**************************************
テクニック
***************************************/
technique tech
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS_DepthMap();
		PixelShader = compile ps_2_0 PS_DepthMap();
	}
	
	pass P1
	{
		VertexShader = compile vs_2_0 VS_DepthShadow();
		PixelShader = compile ps_2_0 PS_DepthShadow();
	}
};