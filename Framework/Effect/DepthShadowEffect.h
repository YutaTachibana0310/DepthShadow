//=====================================
//
// DepthPlotEffect.h
// 機能:深度バッファへのプロットエフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DEPTHPLOTEFFECT_H_
#define _DEPTHPLOTEFFECT_H_

#include "../../main.h"
#include "EffectResource.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class DepthShadowEffect : public EffectResource
{
public:
	DepthShadowEffect();
	~DepthShadowEffect();

	void SetWorldMatrix(const D3DXMATRIX& mtx);
	void SetViewMatrix(const D3DXMATRIX& mtx);
	void SetProjectionMatrix(const D3DXMATRIX& mtx);
	void SetLigjtViewMatrix(const D3DXMATRIX& mtx);
	void SetLightProjectionMatrix(const D3DXMATRIX& mtx);
	void SetLightDirection(const D3DXVECTOR3& dir);
	void SetDepthMap(LPDIRECT3DTEXTURE9 depthMap);

protected:
	D3DXHANDLE hWorldMtx;
	D3DXHANDLE hViewMtx;
	D3DXHANDLE hProjectionMtx;
	D3DXHANDLE hLightViewMtx;
	D3DXHANDLE hLightProjectionMtx;
	D3DXHANDLE hLightDir;
	D3DXHANDLE hDepthMap;
};

#endif