//=====================================
//
//エフェクトリソース処理[EffectResource.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EffectResource.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
EffectResource::EffectResource() :
	effect(NULL), hTech(NULL)
{

}

/**************************************
デストラクタ
***************************************/
EffectResource::~EffectResource()
{
	SAFE_RELEASE(effect);
}

/**************************************
初期化処理
***************************************/
void EffectResource::Init(LPD3DXEFFECT effect)
{
	this->effect = effect;
	effect->AddRef();
}

/**************************************
パス開始宣言
***************************************/
void EffectResource::Begin(UINT * pPasses, DWORD flags)
{
	effect->SetTechnique(hTech);
	effect->Begin(pPasses, flags);
}

/**************************************
パス終了宣言
***************************************/
void EffectResource::End()
{
	effect->End();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
}

/**************************************
描画開始宣言
***************************************/
void EffectResource::BeginPass(DWORD pass)
{
	effect->BeginPass(pass);
}

/**************************************
描画終了宣言
***************************************/
void EffectResource::EndPass()
{
	effect->EndPass();
}

/**************************************
変更のコミット
***************************************/
void EffectResource::CommitChanges()
{
	effect->CommitChanges();
}
