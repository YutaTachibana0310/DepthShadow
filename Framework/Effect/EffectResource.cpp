//=====================================
//
//�G�t�F�N�g���\�[�X����[EffectResource.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EffectResource.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EffectResource::EffectResource() :
	effect(NULL), hTech(NULL)
{

}

/**************************************
�f�X�g���N�^
***************************************/
EffectResource::~EffectResource()
{
	SAFE_RELEASE(effect);
}

/**************************************
����������
***************************************/
void EffectResource::Init(LPD3DXEFFECT effect)
{
	this->effect = effect;
	effect->AddRef();
}

/**************************************
�p�X�J�n�錾
***************************************/
void EffectResource::Begin(UINT * pPasses, DWORD flags)
{
	effect->SetTechnique(hTech);
	effect->Begin(pPasses, flags);
}

/**************************************
�p�X�I���錾
***************************************/
void EffectResource::End()
{
	effect->End();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
}

/**************************************
�`��J�n�錾
***************************************/
void EffectResource::BeginPass(DWORD pass)
{
	effect->BeginPass(pass);
}

/**************************************
�`��I���錾
***************************************/
void EffectResource::EndPass()
{
	effect->EndPass();
}

/**************************************
�ύX�̃R�~�b�g
***************************************/
void EffectResource::CommitChanges()
{
	effect->CommitChanges();
}
