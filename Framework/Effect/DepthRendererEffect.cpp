//=====================================
//
//テンプレート処理[DepthRendererEffect.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "DepthRendererEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
コンストラクタ
***************************************/
DepthRendererEffect::DepthRendererEffect() :
	hWorldMtx(0), hViewMtx(0), hProjectionMtx(0)
{
	const char* EffectPath = "data/Effect/DepthRenderer.cfx";

	Init(ResourceManager::Instance()->GetEffect(EffectPath));

	hWorldMtx = effect->GetParameterByName(0, "mtxWorld");
	hViewMtx = effect->GetParameterByName(0, "mtxView");
	hProjectionMtx = effect->GetParameterByName(0, "mtxProjection");

	effect->SetTechnique("tech");
}

/**************************************
デストラクタ
***************************************/
DepthRendererEffect::~DepthRendererEffect()
{
}

/**************************************
ワールド行列設定処理
***************************************/
void DepthRendererEffect::SetWorldMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hWorldMtx, &mtx);
}

/**************************************
ビュー行列設定処理
***************************************/
void DepthRendererEffect::SetViewMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hViewMtx, &mtx);
}

/**************************************
プロジェクション行列設定処理
***************************************/
void DepthRendererEffect::SetProjectionMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hProjectionMtx, &mtx);
}
