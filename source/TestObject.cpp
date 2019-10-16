//=====================================
//
//テンプレート処理[TestObject.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TestObject.h"
#include "../Framework/Camera/Camera.h"
#include "../Framework/Resource/ResourceManager.h"
#include "../Framework/Renderer3D/MeshContainer.h"
#include "../Framework/Effect/DepthShadowEffect.h"
#include "../Framework/Effect/DepthRendererEffect.h"

/**************************************
グローバル変数
***************************************/
TestObject::TestObject()
{
	ResourceManager::Instance()->LoadMesh("Test", "data/MODEL/cube00.x");

	mesh = MeshContainer::Create();
	ResourceManager::Instance()->GetMesh("Test", mesh);

	effect = new DepthShadowEffect();
	depthRenderer = new DepthRendererEffect();
}

TestObject::~TestObject()
{
	SAFE_DELETE(mesh);
	SAFE_DELETE(effect);
	SAFE_DELETE(depthRenderer);
}

void TestObject::Draw()
{
#if 1
	effect->SetWorldMatrix(transform->GetMatrix());

	effect->Begin(0, 0);
	effect->BeginPass(0);
	mesh->Draw();
	effect->EndPass();
	effect->End();
#else
	transform->SetWorld();
	mesh->Draw();
#endif
}

void TestObject::DrawDepth()
{
	depthRenderer->SetWorldMatrix(transform->GetMatrix());

	depthRenderer->Begin(0, 0);
	depthRenderer->BeginPass(0);
	mesh->Draw();
	depthRenderer->EndPass();
	depthRenderer->End();
}
