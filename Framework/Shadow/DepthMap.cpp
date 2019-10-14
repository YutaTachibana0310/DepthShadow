//=====================================
//
//深度マップ処理[DepthMap.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "DepthMap.h"

/**************************************
コンストラクタ
***************************************/
DepthMap::DepthMap() :
	texture(NULL), surface(NULL), depthBuffer(NULL), defaultRenderTarget(NULL), defaultDepthBuffer(NULL)
{
}

/**************************************
デストラクタ
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
初期化処理
***************************************/
void DepthMap::Init(UINT width, UINT height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Z値テクスチャを作成
	D3DXCreateTexture(pDevice, width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture);
	texture->GetSurfaceLevel(0, &surface);

	//デプスバッファサーフェイスの作成
	D3DSURFACE_DESC desc;
	surface->GetDesc(&desc);
	UINT depthWidth = desc.Width;
	UINT depthHeight = desc.Height;
	pDevice->CreateDepthStencilSurface(depthWidth, depthHeight, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, 0, &depthBuffer, 0);
}

/**************************************
プロット開始処理
***************************************/
void DepthMap::Begin()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//デバイスが持っているばバッファを一時保存
	pDevice->GetRenderTarget(0, &defaultRenderTarget);
	pDevice->GetDepthStencilSurface(&defaultDepthBuffer);

	//デバイスにZ値テクスチャサーフェイスと深度バッファを設定
	pDevice->SetRenderTarget(0, surface);
	pDevice->SetDepthStencilSurface(depthBuffer);

	//各サーフェイス初期化
	pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0);
}

/**************************************
プロット終了処理
***************************************/
void DepthMap::End()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//デバイスのサーフェイスをもとに戻す
	pDevice->SetRenderTarget(0, defaultRenderTarget);
	pDevice->SetDepthStencilSurface(defaultDepthBuffer);

	//解放
	SAFE_RELEASE(defaultRenderTarget);
	SAFE_RELEASE(defaultDepthBuffer);
}

/**************************************
深度マップ取得処理
***************************************/
LPDIRECT3DTEXTURE9 DepthMap::GetTexture()
{
	return texture;
}
