//=====================================
//
// TestField.h
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TESTFIELD_H_
#define _TESTFIELD_H_

#include "../main.h"

/**************************************
�O���錾
***************************************/
class BoardPolygon;
class DepthShadowEffect;

/**************************************
�N���X��`
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
};

#endif