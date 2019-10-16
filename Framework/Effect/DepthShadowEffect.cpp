//=====================================
//
//深度バッファへのプロットエフェクト処理[DepthShadowEffect.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "DepthShadowEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
staticメンバ
***************************************/
D3DXMATRIX DepthShadowEffect::mtxView;
D3DXMATRIX DepthShadowEffect::mtxProjection;
D3DXMATRIX DepthShadowEffect::mtxLightView;
D3DXMATRIX DepthShadowEffect::mtxLightProjection;
D3DXMATRIX DepthShadowEffect::mtxTexture;

/**************************************
コンストラクタ
***************************************/
DepthShadowEffect::DepthShadowEffect() :
	hMtxWVP(0), hMtxLWVP(0), hMtxLWVPT(0), hLightDir(0)
{
	const char* EffectPath = "data/Effect/DepthShadow.cfx";

	Init(ResourceManager::Instance()->GetEffect(EffectPath));

	hTech = effect->GetTechniqueByName("tech");
	hMtxWVP = effect->GetParameterByName(0, "mtxWVP");
	hMtxLWVP = effect->GetParameterByName(0, "mtxLWVP");
	hMtxLWVPT = effect->GetParameterByName(0, "mtxLWVPT");
	hLightDir = effect->GetParameterByName(0, "lightDir");

	D3DXMatrixIdentity(&mtxView);
	D3DXMatrixIdentity(&mtxProjection);
	D3DXMatrixIdentity(&mtxLightView);
	D3DXMatrixIdentity(&mtxLightProjection);

	D3DXMATRIX texScale, texTranslation;
	D3DXMatrixScaling(&texScale, 0.5f, -0.5f, 1.0f);
	D3DXMatrixTranslation(&texTranslation, 0.5f, 0.5f, 0.0f);
	mtxTexture = texScale * texTranslation;

	effect->SetTechnique(hTech);
}

/**************************************
デストラクタ
***************************************/
DepthShadowEffect::~DepthShadowEffect()
{

}

/**************************************
ワールド行列設定処理
***************************************/
void DepthShadowEffect::SetWorldMatrix(const D3DXMATRIX & mtx)
{
	D3DXMATRIX WVP = mtx * mtxView * mtxProjection;
	D3DXMATRIX LWVP = mtx * mtxLightView * mtxLightProjection;
	D3DXMATRIX LWVPT = LWVP * mtxTexture;

	effect->SetMatrix(hMtxWVP, &WVP);
	effect->SetMatrix(hMtxLWVP, &LWVP);
	effect->SetMatrix(hMtxLWVPT, &LWVPT);
}

/**************************************
ビュー行列設定処理
***************************************/
void DepthShadowEffect::SetViewMatrix(const D3DXMATRIX & mtx)
{
	mtxView = mtx;
}

/**************************************
プロジェクション行列設定処理
***************************************/
void DepthShadowEffect::SetProjectionMatrix(const D3DXMATRIX & mtx)
{
	mtxProjection = mtx;
}

/**************************************
ライトビュー行列設定処理
***************************************/
void DepthShadowEffect::SetLigjtViewMatrix(const D3DXMATRIX & mtx)
{
	mtxLightView = mtx;
}

/**************************************
ライトプロジェクション行列設定処理
***************************************/
void DepthShadowEffect::SetLightProjectionMatrix(const D3DXMATRIX & mtx)
{
	mtxLightProjection = mtx;
}

/**************************************
ライト方向設定処理
***************************************/
void DepthShadowEffect::SetLightDirection(const D3DXVECTOR3 & dir)
{
	effect->SetFloatArray(hLightDir, (float*)&dir, 3);
}
