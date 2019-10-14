//=====================================
//
// DepthRenderer.fx
// �@�\:Z�l�����_�����O�V�F�[�_
// Author:GP12B332 21 ���ԗY��
//
//=====================================

/**************************************
�O���[�o���ϐ�
***************************************/
float4x4 mtxWorld;				//���[���h�s��
float4x4 mtxView;				//�r���[�s��
float4x4 mtxProjection;			//�v���W�F�N�V�����s��
float4x4 mtxLightView;			//���C�g�r���[�ϊ��s��
float4x4 mtxLightProjection;	//���C�g�ˉe�ϊ��s��
float3 lightDir;

texture depthMap;				//�[�x�}�b�v

/**************************************
�e�N�X�`���T���v��
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
���_�V�F�[�_�o�͍\����
***************************************/
struct DepthMapOutput
{
	float4 pos : POSITION;
	float4 shadowMapTex : TEXCOORD0;
};

/**************************************
�[�x�}�b�v�쐬���_�V�F�[�_
***************************************/
DepthMapOutput VS_DepthMap(float4 pos : POSITION)
{
	DepthMapOutput Out = (DepthMapOutput)0;

	//���[���h�r���[�v���W�F�N�V�����ϊ�
	Out.pos = mul(pos, mtxWorld);
	Out.pos = mul(Out.pos, mtxLightView);
	Out.pos = mul(Out.pos, mtxLightProjection);
	
	//�e�N�X�`�����W�𒸓_�ɍ��킹��
	Out.shadowMapTex = Out.pos;

	return Out;
}

/**************************************
�[�x�}�b�v�쐬�s�N�Z���V�F�[�_
***************************************/
float4 PS_DepthMap(float4 shadowMapTex : TEXCOORD0) : COLOR0
{
	//Z�l�Z�o
	float4 color = shadowMapTex.z / shadowMapTex.w;
	color.a = 1.0f;
	return color;
}

/**************************************
�[�x�o�b�t�@�V���h�E���_�V�F�[�_�o�͍\����
***************************************/
struct DepthShadowOutput
{
	float4 pos : POSITION;
	float4 zCalcTex : COLOR1;
	float4 color : COLOR0;
};

/**************************************
�[�x�o�b�t�@�V���h�E���_�V�F�[�_
***************************************/
DepthShadowOutput VS_DepthShadow(
	float4 pos : POSITION,
	float3 normal : NORMAL)
{
	DepthShadowOutput Out = (DepthShadowOutput)0;

	//�J�����̖ڐ��ɂ��WVP�ϊ�
	Out.pos = mul(pos, mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);

	//���C�g�̖ڐ��ɂ��WVP�ϊ�
	Out.zCalcTex = mul(pos, mtxWorld);
	Out.zCalcTex = mul(Out.zCalcTex, mtxLightView);
	Out.zCalcTex = mul(Out.zCalcTex, mtxLightProjection);

	//�J���[���v�Z
	float3 N = normalize(mul(normal, mtxWorld));
	float lightDot = max(0.0f, dot(N, -lightDir));
	Out.color = float4(0.0f, 0.5f, 1.0f, 1.0f) * lightDot;
	Out.color.w = 1.0f;

	return Out;
}

/**************************************
�[�x�o�b�t�@�V���h�E�s�N�Z���V�F�[�_
***************************************/
float4 PS_DepthShadow(
	float4 color : COLOR0,
	float4 zCalcTex : COLOR1) : COLOR
{
	//���C�g�ڐ��ɂ��Z�l�̍ĎZ�o
	float zValue = zCalcTex.z / zCalcTex.w;

	//�ˉe��Ԃ�XY���W���e�N�X�`�����W�ɕϊ�
	float2 transTexCoord;
	transTexCoord.x = (1.0f + zCalcTex.x / zCalcTex.w) * 0.5f;
	transTexCoord.y = (1.0f - zCalcTex.y / zCalcTex.w) * 0.5f;

	//���A��Z�l���o
	float realZ = tex2D(depthMapSampler, transTexCoord).x;

	if (zValue > realZ + 0.005f)
	{
		color.rgb = float3(1.0f, 1.0f, 1.0f) -  color.rgb;
		//color.rgb = color.rgb * 0.5f;
	}

	return color;
}

/**************************************
�e�N�j�b�N
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