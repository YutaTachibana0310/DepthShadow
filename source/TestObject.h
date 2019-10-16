//=====================================
//
// TestObject.h
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TESTOBJECT_H_
#define _TESTOBJECT_H_

#include "../main.h"

/**************************************
�O���錾
***************************************/
class MeshContainer;
class DepthShadowEffect;
class DepthRendererEffect;

/**************************************
�N���X��`
***************************************/
class TestObject : public GameObject
{
public:
	TestObject();
	~TestObject();

	void Draw();
	void DrawDepth();

private:
	MeshContainer *mesh;
	DepthShadowEffect *effect;
	DepthRendererEffect *depthRenderer;
};

#endif