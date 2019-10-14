//=====================================
//
//�[�x�o�b�t�@�ւ̃v���b�g�G�t�F�N�g����[DepthShadowEffect.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "DepthShadowEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
�R���X�g���N�^
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
�f�X�g���N�^
***************************************/
DepthShadowEffect::~DepthShadowEffect()
{

}

/**************************************
���[���h�s��ݒ菈��
***************************************/
void DepthShadowEffect::SetWorldMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hWorldMtx, &mtx);
}

/**************************************
�r���[�s��ݒ菈��
***************************************/
void DepthShadowEffect::SetViewMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hViewMtx, &mtx);
}

/**************************************
�v���W�F�N�V�����s��ݒ菈��
***************************************/
void DepthShadowEffect::SetProjectionMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hProjectionMtx, &mtx);
}

/**************************************
���C�g�r���[�s��ݒ菈��
***************************************/
void DepthShadowEffect::SetLigjtViewMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hLightViewMtx, &mtx);
}

/**************************************
���C�g�v���W�F�N�V�����s��ݒ菈��
***************************************/
void DepthShadowEffect::SetLightProjectionMatrix(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hLightProjectionMtx, &mtx);
}

/**************************************
���C�g�����ݒ菈��
***************************************/
void DepthShadowEffect::SetLightDirection(const D3DXVECTOR3 & dir)
{
	effect->SetFloatArray(hLightDir, (float*)&dir, 3);
}

/**************************************
�[�x�}�b�v�ݒ菈��
***************************************/
void DepthShadowEffect::SetDepthMap(LPDIRECT3DTEXTURE9 depthMap)
{
	HRESULT res = effect->SetTexture(hDepthMap, depthMap);
}
