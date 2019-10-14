//=====================================
//
//テンプレート処理[TestField.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TestField.h"
#include "../Framework/Renderer3D/BoardPolygon.h"
#include "../Framework/Effect/DepthShadowEffect.h"
#include "../Framework/Tool/DebugWindow.h"

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
TestField::TestField()
{
	polygon = new BoardPolygon();
	polygon->LoadTexture("data/TEXTURE/field.jpg");
	polygon->SetSize({ 200.0f, 200.0f });
	transform->Move(Vector3::Down * 10.0f);
	transform->Rotate(90.0f, Vector3::Right);

	effect = new DepthShadowEffect();
}

TestField::~TestField()
{
	SAFE_DELETE(polygon);
	SAFE_DELETE(effect);
}

void TestField::Draw()
{
	Debug::Begin("Field");
	static D3DXVECTOR3 pos{ 0.0f, -10.0f, 0.0f };
	Debug::Slider("pos", pos, { 0.0f, -50.0f, 0.0f }, Vector3::Up * 50.0f);
	Debug::End();
	transform->SetPosition(pos);
#if 1
	effect->SetWorldMatrix(transform->GetMatrix());

	effect->Begin(0, 0);
	effect->BeginPass(1);
	polygon->Draw();
	effect->EndPass();
	effect->End();
#else 
	transform->SetWorld();
	polygon->Draw();
#endif
}

void TestField::DrawDepth()
{
	effect->SetWorldMatrix(transform->GetMatrix());
	
	effect->Begin(0, 0);
	effect->BeginPass(0);
	polygon->Draw();
	effect->EndPass();
	effect->End();
}
