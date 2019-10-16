//=====================================
//
//�e���v���[�g����[DepthRendererEffect.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "DepthRendererEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
�R���X�g���N�^
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
�f�X�g���N�^
***************************************/
DepthRendererEffect::~DepthRendererEffect()
{
}

/**************************************
���[���h�s��ݒ菈��
***************************************/
void DepthRendererEffect::SetWorldMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hWorldMtx, &mtx);
}

/**************************************
�r���[�s��ݒ菈��
***************************************/
void DepthRendererEffect::SetViewMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hViewMtx, &mtx);
}

/**************************************
�v���W�F�N�V�����s��ݒ菈��
***************************************/
void DepthRendererEffect::SetProjectionMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hProjectionMtx, &mtx);
}
