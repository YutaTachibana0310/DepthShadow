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

/**************************************
グローバル変数
***************************************/
TestObject::TestObject()
{
	ResourceManager::Instance()->LoadMesh("Test", "data/MODEL/cube00.x");

	mesh = MeshContainer::Create();
	ResourceManager::Instance()->GetMesh("Test", mesh);

	effect = new DepthShadowEffect();
}

TestObject::~TestObject()
{
	SAFE_DELETE(mesh);
	SAFE_DELETE(effect);
}

void TestObject::Draw()
{
#if 1
	effect->SetWorldMatrix(transform->GetMatrix());

	effect->Begin(0, 0);
	effect->BeginPass(1);
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
	effect->SetWorldMatrix(transform->GetMatrix());

	effect->Begin(0, 0);
	effect->BeginPass(0);
	mesh->Draw();
	effect->EndPass();
	effect->End();
}

/**************************************
変換行列取得処理
***************************************/
D3DXMATRIX TestObject::GetMatrix()
{
	D3DXMATRIX mtxWorld = transform->GetMatrix();
	D3DXMATRIX mtxView = Camera::MainCamera()->GetViewMtx();
	D3DXMATRIX mtxProj = Camera::MainCamera()->GetProjectionMtx();

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxView);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxProj);

	return mtxWorld;
}
