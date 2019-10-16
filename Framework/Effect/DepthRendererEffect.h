//=====================================
//
// DepthRendererEffect.h
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DEPTHRENDEREREFFECT_H_
#define _DEPTHRENDEREREFFECT_H_

#include "../../main.h"
#include "EffectResource.h"
/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class DepthRendererEffect : public EffectResource
{
public:
	DepthRendererEffect();
	~DepthRendererEffect();

	void SetWorldMatrix(const D3DXMATRIX& mtx);
	void SetViewMatrix(const D3DXMATRIX& mtx);
	void SetProjectionMatrix(const D3DXMATRIX& mtx);

protected:
	D3DXHANDLE hWorldMtx;
	D3DXHANDLE hViewMtx;
	D3DXHANDLE hProjectionMtx;
};

#endif