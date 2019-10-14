//=====================================
//
// EffectResource.h
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EFFECTRESOURCE_H_
#define _EFFECTRESOURCE_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class EffectResource
{
public:
	//コンストラクタ、デストラクタ
	EffectResource();
	virtual ~EffectResource();

	//初期化処理
	virtual void Init(LPD3DXEFFECT effect);

	//描画開始宣言
	virtual void Begin(UINT* pPasses, DWORD flags);

	//描画終了宣言
	virtual void End();

	//パス開始宣言
	virtual void BeginPass(DWORD pass);

	//パス終了宣言
	virtual void EndPass();

	//変更コミット宣言
	virtual void CommitChanges();

protected:
	LPD3DXEFFECT effect;
	D3DXHANDLE hTech;
};

#endif