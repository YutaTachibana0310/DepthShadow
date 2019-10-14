//=====================================
//
//���m�g�[���t�B���^����[MonotoneFilter.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MonotoneFilter.h"
#include "../../Math/TMath.h"

/**************************************
�}�N����`
***************************************/
#define EFFECTFILE_MONOTONE_PATH	"PostEffect/MonotoneFilter.fx"
#define PRECOMPILE_MONOTONE_PATH	"data/EFFECT/MonotoneFilter.cfx"

/**************************************
�O���[�o���ϐ�
***************************************/
MonotoneFilter* MonotoneFilter::instance = NULL;

/**************************************
�C���X�^���X�Q�Ə���
***************************************/
MonotoneFilter* MonotoneFilter::Instance()
{
	if (MonotoneFilter::instance == NULL)
		MonotoneFilter::instance = new MonotoneFilter();

	return MonotoneFilter::instance;
}

/**************************************
�C���X�^���X�������
***************************************/
void MonotoneFilter::Destroy()
{
	delete MonotoneFilter::instance;
}

/**************************************
�R���X�g���N�^
***************************************/
MonotoneFilter::MonotoneFilter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	HRESULT res = D3DXCreateEffectFromFile(pDevice, (LPSTR)PRECOMPILE_MONOTONE_PATH, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	if(!res)
		D3DXCreateEffectFromFile(pDevice, (LPSTR)EFFECTFILE_MONOTONE_PATH, 0, 0, 0, 0, &effect, 0);

	effect->SetTechnique("tech");
	hndlPower = effect->GetParameterByName(0, "power");
}

/**************************************
�f�X�g���N�^
***************************************/
MonotoneFilter::~MonotoneFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void MonotoneFilter::Draw()
{
	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
�����ݒ菈��
***************************************/
void MonotoneFilter::SetPower(float power)
{
	effect->SetFloat(hndlPower, Math::Clamp(0.0f, 1.0f, power));
	effect->CommitChanges();
}