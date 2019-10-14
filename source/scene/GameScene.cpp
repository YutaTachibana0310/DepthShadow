//=====================================
//
//テンプレート処理[GameScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "../TestObject.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"
#include "../../Framework/Shadow/DepthMap.h"
#include "../../Framework/Effect/DepthShadowEffect.h"
#include "../TestField.h"

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const int ObjectNum = 15;
	object.resize(ObjectNum * ObjectNum, NULL);
	for (auto&& obj : object)
	{
		obj = new TestObject();
	}

	field = new TestField();
	
	effect = new DepthShadowEffect();

	const float Offset = 10.0f;
	const float Scale = 0.2f;
	const float Base = ObjectNum * 0.5f * Offset;
	for (int i = 0; i < ObjectNum; i++)
	{
		for (int j = 0; j < ObjectNum; j++)
		{
			object[i * ObjectNum + j]->SetPosition({ Offset * i - Base, 5.0f, Offset * j - 30.0f});
			object[i * ObjectNum + j]->SetScale(Vector3::One * Scale);
		}
	}

	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	//深度マップ作成
	depthMap = new DepthMap();

	//デバイスのデプスバッファの幅と高さを取得
	LPDIRECT3DSURFACE9 tmpSuf;
	UINT width, height;
	pDevice->GetDepthStencilSurface(&tmpSuf);
	GameScene::GetSurfaceWidthHeight(tmpSuf, width, height);
	SAFE_RELEASE(tmpSuf);

	depthMap->Init(width, height);

	effect->SetDepthMap(depthMap->GetTexture());
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	Utility::DeleteContainer(object);

	SAFE_DELETE(field);
	SAFE_DELETE(effect);
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(depthMap);
}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	sceneCamera->Update();
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	sceneCamera->Set();

	Debug::Begin("Light");
	static D3DXVECTOR3 light{ 0.8f, -1.0f, 0.8f };
	Debug::Slider("dir", light, Vector3::One* -1.0f, Vector3::One);
	Debug::End();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX lightView, lightProjection;
	D3DXVECTOR3 normalizeLight;
	D3DXVec3Normalize(&normalizeLight, &light);

	D3DXMatrixPerspectiveFovLH(&lightProjection,
		D3DXToRadian(60.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		500.0f);

	D3DXMatrixLookAtLH(&lightView, 
		&(normalizeLight * -50.0f), 
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(0, 1, 0));

	effect->SetViewMatrix(sceneCamera->GetViewMtx());
	effect->SetProjectionMatrix(sceneCamera->GetProjectionMtx());
	effect->SetLigjtViewMatrix(lightView);
	effect->SetLightProjectionMatrix(lightProjection);
	effect->SetLightDirection(normalizeLight);

	//Z値テクスチャに描画
	depthMap->Begin();
	for (auto&& obj : object)
	{
		obj->DrawDepth();
	}
	field->DrawDepth();
	depthMap->End();

	effect->SetDepthMap(depthMap->GetTexture());
	effect->CommitChanges();
	//通常描画
	for (auto&& obj : object)
	{
		obj->Draw();
	}
	field->Draw();

	Debug::Begin("Depth");
	Debug::DrawTexture(depthMap->GetTexture(), D3DXVECTOR2(500.0f, 250.0f));
	Debug::End();
}

/**************************************
サーフェイスの幅高さ取得処理
***************************************/
bool GameScene::GetSurfaceWidthHeight(LPDIRECT3DSURFACE9 surf, UINT & width, UINT& height)
{
	if (!surf)
		return false;

	D3DSURFACE_DESC desc;
	surf->GetDesc(&desc);
	width = desc.Width;
	height = desc.Height;
	return true;
}
