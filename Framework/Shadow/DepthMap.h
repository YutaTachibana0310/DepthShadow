//=====================================
//
// DepthMap.h
// �@�\:�[�x�}�b�v
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DEPTHMAP_H_
#define _DEPTHMAP_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class DepthMap
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	DepthMap();
	~DepthMap();

	//�[�x�}�b�v�̕��A������n���ď��������鏈��
	void Init(UINT width, UINT height);

	//�[�x�}�b�v�ւ̃v���b�g�J�n����
	void Begin();

	//�[�x�}�b�v�ւ̃v���b�g�I������
	void End();

	//�[�x�}�b�v�擾����
	LPDIRECT3DTEXTURE9 GetTexture();

protected:
	LPDIRECT3DTEXTURE9 texture;					//Z�l�e�N�X�`��
	LPDIRECT3DSURFACE9 surface;					//Z�l�e�N�X�`���T�[�t�F�C�X
	LPDIRECT3DSURFACE9 depthBuffer;				//�k�x�o�b�t�@
	LPDIRECT3DSURFACE9 defaultRenderTarget;		//���̃����_�[�^�[�Q�b�g
	LPDIRECT3DSURFACE9 defaultDepthBuffer;		//���̐k�x�o�b�t�@
};

#endif