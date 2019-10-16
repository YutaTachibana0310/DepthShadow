//=====================================
//
// GameScene.h
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class TestObject;
class TestField;
class DepthMap;
class DepthShadowEffect;
class DepthRendererEffect;

/**************************************
クラス定義
***************************************/
class GameScene : public BaseScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetSurfaceWidthHeight(LPDIRECT3DSURFACE9 surf, UINT& width, UINT& height);

private:
	std::vector<TestObject*> object;
	TestField *field;

	DepthMap *depthMap;
	DepthShadowEffect *effect;
	DepthRendererEffect *depthRenderer;
};

#endif