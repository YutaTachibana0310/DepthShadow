//=====================================
//
//GameMain.cpp
//機能:ゲームメイン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameMain.h"
#include "../Framework/Core/SceneManager.h"

#include "Scene\GameScene.h"

/**************************************
コンストラクタ
***************************************/
GameMain::GameMain(HINSTANCE hInstance, HWND hWnd) :
	BaseGame(hInstance, hWnd)
{
	//シーンマネージャにシーンのインスタンスを追加
	sceneManager->Add(0, new GameScene());

	//初期シーンに遷移
	const int InitScene = 0;
	sceneManager->ChangeScene(InitScene);
}