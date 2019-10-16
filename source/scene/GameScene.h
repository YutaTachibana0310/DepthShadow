//=====================================
//
// GameScene.h
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class TestObject;
class TestField;
class DepthMap;
class DepthShadowEffect;
class DepthRendererEffect;

/**************************************
�N���X��`
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