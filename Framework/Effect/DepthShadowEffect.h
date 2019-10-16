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

protected:
	D3DXHANDLE hMtxWVP;
	D3DXHANDLE hMtxLWVP;
	D3DXHANDLE hMtxLWVPT;
	D3DXHANDLE hLightDir;

	static D3DXMATRIX mtxView;
	static D3DXMATRIX mtxProjection;
	static D3DXMATRIX mtxLightView;
	static D3DXMATRIX mtxLightProjection;
	static D3DXMATRIX mtxTexture;
};

#endif