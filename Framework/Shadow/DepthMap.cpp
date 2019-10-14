//=====================================
//
//�[�x�}�b�v����[DepthMap.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "DepthMap.h"

/**************************************
�R���X�g���N�^
***************************************/
DepthMap::DepthMap() :
	texture(NULL), surface(NULL), depthBuffer(NULL), defaultRenderTarget(NULL), defaultDepthBuffer(NULL)
{
}

/**************************************
�f�X�g���N�^
***************************************/
DepthMap::~DepthMap()
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(surface);
	SAFE_RELEASE(depthBuffer);
	SAFE_RELEASE(defaultRenderTarget);
	SAFE_RELEASE(defaultDepthBuffer);
}

/**************************************
����������
***************************************/
void DepthMap::Init(UINT width, UINT height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Z�l�e�N�X�`�����쐬
	D3DXCreateTexture(pDevice, width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture);
	texture->GetSurfaceLevel(0, &surface);

	//�f�v�X�o�b�t�@�T�[�t�F�C�X�̍쐬
	D3DSURFACE_DESC desc;
	surface->GetDesc(&desc);
	UINT depthWidth = desc.Width;
	UINT depthHeight = desc.Height;
	pDevice->CreateDepthStencilSurface(depthWidth, depthHeight, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, 0, &depthBuffer, 0);
}

/**************************************
�v���b�g�J�n����
***************************************/
void DepthMap::Begin()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�o�C�X�������Ă���΃o�b�t�@���ꎞ�ۑ�
	pDevice->GetRenderTarget(0, &defaultRenderTarget);
	pDevice->GetDepthStencilSurface(&defaultDepthBuffer);

	//�f�o�C�X��Z�l�e�N�X�`���T�[�t�F�C�X�Ɛ[�x�o�b�t�@��ݒ�
	pDevice->SetRenderTarget(0, surface);
	pDevice->SetDepthStencilSurface(depthBuffer);

	//�e�T�[�t�F�C�X������
	pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0);
}

/**************************************
�v���b�g�I������
***************************************/
void DepthMap::End()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�o�C�X�̃T�[�t�F�C�X�����Ƃɖ߂�
	pDevice->SetRenderTarget(0, defaultRenderTarget);
	pDevice->SetDepthStencilSurface(defaultDepthBuffer);

	//���
	SAFE_RELEASE(defaultRenderTarget);
	SAFE_RELEASE(defaultDepthBuffer);
}

/**************************************
�[�x�}�b�v�擾����
***************************************/
LPDIRECT3DTEXTURE9 DepthMap::GetTexture()
{
	return texture;
}
