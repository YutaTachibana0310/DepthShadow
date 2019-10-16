//=====================================
//
//�[�x�o�b�t�@�ւ̃v���b�g�G�t�F�N�g����[DepthShadowEffect.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "DepthShadowEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
static�����o
***************************************/
D3DXMATRIX DepthShadowEffect::mtxView;
D3DXMATRIX DepthShadowEffect::mtxProjection;
D3DXMATRIX DepthShadowEffect::mtxLightView;
D3DXMATRIX DepthShadowEffect::mtxLightProjection;
D3DXMATRIX DepthShadowEffect::mtxTexture;

/**************************************
�R���X�g���N�^
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
	D3DXMATRIX WVP = mtx * mtxView * mtxProjection;
	D3DXMATRIX LWVP = mtx * mtxLightView * mtxLightProjection;
	D3DXMATRIX LWVPT = LWVP * mtxTexture;

	effect->SetMatrix(hMtxWVP, &WVP);
	effect->SetMatrix(hMtxLWVP, &LWVP);
	effect->SetMatrix(hMtxLWVPT, &LWVPT);
}

/**************************************
�r���[�s��ݒ菈��
***************************************/
void DepthShadowEffect::SetViewMatrix(const D3DXMATRIX & mtx)
{
	mtxView = mtx;
}

/**************************************
�v���W�F�N�V�����s��ݒ菈��
***************************************/
void DepthShadowEffect::SetProjectionMatrix(const D3DXMATRIX & mtx)
{
	mtxProjection = mtx;
}

/**************************************
���C�g�r���[�s��ݒ菈��
***************************************/
void DepthShadowEffect::SetLigjtViewMatrix(const D3DXMATRIX & mtx)
{
	mtxLightView = mtx;
}

/**************************************
���C�g�v���W�F�N�V�����s��ݒ菈��
***************************************/
void DepthShadowEffect::SetLightProjectionMatrix(const D3DXMATRIX & mtx)
{
	mtxLightProjection = mtx;
}

/**************************************
���C�g�����ݒ菈��
***************************************/
void DepthShadowEffect::SetLightDirection(const D3DXVECTOR3 & dir)
{
	effect->SetFloatArray(hLightDir, (float*)&dir, 3);
}
