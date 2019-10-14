//=====================================
//
// DepthMap.h
// 機能:深度マップ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DEPTHMAP_H_
#define _DEPTHMAP_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class DepthMap
{
public:
	//コンストラクタ、デストラクタ
	DepthMap();
	~DepthMap();

	//深度マップの幅、高さを渡して初期化する処理
	void Init(UINT width, UINT height);

	//深度マップへのプロット開始処理
	void Begin();

	//深度マップへのプロット終了処理
	void End();

	//深度マップ取得処理
	LPDIRECT3DTEXTURE9 GetTexture();

protected:
	LPDIRECT3DTEXTURE9 texture;					//Z値テクスチャ
	LPDIRECT3DSURFACE9 surface;					//Z値テクスチャサーフェイス
	LPDIRECT3DSURFACE9 depthBuffer;				//震度バッファ
	LPDIRECT3DSURFACE9 defaultRenderTarget;		//元のレンダーターゲット
	LPDIRECT3DSURFACE9 defaultDepthBuffer;		//元の震度バッファ
};

#endif