//=====================================
//
// TestField.h
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TESTFIELD_H_
#define _TESTFIELD_H_

#include "../main.h"

/**************************************
前方宣言
***************************************/
class BoardPolygon;
class DepthShadowEffect;
class DepthRendererEffect;

/**************************************
クラス定義
***************************************/
class TestField : GameObject
{
public:
	TestField();
	~TestField();

	void Draw();
	void DrawDepth();

private:
	BoardPolygon *polygon;
	DepthShadowEffect *effect;
	DepthRendererEffect *depthRenderer;
};

#endif