//=====================================
//
//深度バッファへのプロットエフェクト処理[DepthShadowEffect.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "DepthShadowEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
コンストラクタ
***************************************/
DepthShadowEffect::DepthShadowEffect() :
	hWorldMtx(NULL), hViewMtx(NULL), hProjectionMtx(NULL), hLightViewMtx(NULL), hLightProjectionMtx(NULL), hDepthMap(NULL)
{
	const char* EffectPath = "data/Effect/DepthRenderer.cfx";

	Init(ResourceManager::Instance()->GetEffect(EffectPath));

	hTech = effect->GetTechniqueByName("tech");
	hWorldMtx = effect->GetParameterByName(0, "mtxWorld");
	hViewMtx = effect->GetParameterByName(0, "mtxView");
	hProjectionMtx = effect->GetParameterByName(0, "mtxProjection");
	hLightViewMtx = effect->GetParameterByName(0, "mtxLightView");
	hLightProjectionMtx = effect->GetParameterByName(0, "mtxLightProjection");
	hLightDir = effect->GetParameterByName(0, "lightDir");
	hDepthMap = effect->GetParameterByName(0, "depthMap");

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
	effect->SetMatrix(hWorldMtx, &mtx);
}

/**************************************
ビュー行列設定処理
***************************************/
void DepthShadowEffect::SetViewMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hViewMtx, &mtx);
}

/**************************************
プロジェクション行列設定処理
***************************************/
void DepthShadowEffect::SetProjectionMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hProjectionMtx, &mtx);
}

/**************************************
ライトビュー行列設定処理
***************************************/
void DepthShadowEffect::SetLigjtViewMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hLightViewMtx, &mtx);
}

/**************************************
ライトプロジェクション行列設定処理
***************************************/
void DepthShadowEffect::SetLightProjectionMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hLightProjectionMtx, &mtx);
}

/**************************************
ライト方向設定処理
***************************************/
void DepthShadowEffect::SetLightDirection(const D3DXVECTOR3 & dir)
{
	effect->SetFloatArray(hLightDir, (float*)&dir, 3);
}

/**************************************
深度マップ設定処理
***************************************/
void DepthShadowEffect::SetDepthMap(LPDIRECT3DTEXTURE9 depthMap)
{
	HRESULT res = effect->SetTexture(hDepthMap, depthMap);
}
