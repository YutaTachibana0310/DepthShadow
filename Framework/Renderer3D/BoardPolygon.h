//=====================================
//
//�|���S���w�b�_[BoardPolygon.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOARDPOLYGON_H_
#define _BOARDPOLYGON_H_

#include "../../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class BoardPolygon
{
	friend class ResourceManager;
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	BoardPolygon();
	~BoardPolygon();

	//�`�揈��
	void Draw();

	//�e�N�X�`���ǂݍ��ݏ���
	void LoadTexture(const char* path);

	//�T�C�Y�ݒ菈��
	void SetSize(const D3DXVECTOR2& size);

	//UV�����ݒ菈��
	void SetTexDiv(const D3DXVECTOR2& div);

	//�e�N�X�`���ʂ��ԍ��ݒ菈��
	void SetTextureIndex(int index);

	//UV���W�ݒ菈��
	void SetUV(const D3DXVECTOR2& uv);

	void AddRef();

protected:
	LPDIRECT3DDEVICE9 pDevice;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;

	D3DMATERIAL9 material;

	D3DXVECTOR2 texDiv;
	D3DXVECTOR2 texSize;

	UINT cntReference;
};

#endif