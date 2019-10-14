//=====================================
//
// TestObject.h
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TESTOBJECT_H_
#define _TESTOBJECT_H_

#include "../main.h"

/**************************************
前方宣言
***************************************/
class MeshContainer;
class DepthShadowEffect;

/**************************************
クラス定義
***************************************/
class TestObject : public GameObject
{
public:
	TestObject();
	~TestObject();

	void Draw();
	void DrawDepth();
	D3DXMATRIX GetMatrix();

private:
	MeshContainer *mesh;
	DepthShadowEffect *effect;
};

#endif