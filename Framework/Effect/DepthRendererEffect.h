//=====================================
//
// DepthRendererEffect.h
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DEPTHRENDEREREFFECT_H_
#define _DEPTHRENDEREREFFECT_H_

#include "../../main.h"
#include "EffectResource.h"
/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
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