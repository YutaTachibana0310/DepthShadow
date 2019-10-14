//=====================================
//
// EffectResource.h
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EFFECTRESOURCE_H_
#define _EFFECTRESOURCE_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class EffectResource
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	EffectResource();
	virtual ~EffectResource();

	//����������
	virtual void Init(LPD3DXEFFECT effect);

	//�`��J�n�錾
	virtual void Begin(UINT* pPasses, DWORD flags);

	//�`��I���錾
	virtual void End();

	//�p�X�J�n�錾
	virtual void BeginPass(DWORD pass);

	//�p�X�I���錾
	virtual void EndPass();

	//�ύX�R�~�b�g�錾
	virtual void CommitChanges();

protected:
	LPD3DXEFFECT effect;
	D3DXHANDLE hTech;
};

#endif