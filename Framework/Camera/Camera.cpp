//=====================================
//
//�J��������[Camera.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "Camera.h"
#include "CameraShakePlugin.h"
#include <algorithm>

/**************************************
static�����o
***************************************/
Camera* Camera::mainCamera = NULL;

/**************************************
�R���X�g���N�^
***************************************/
Camera::Camera()
{
	const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, 10.0f, -50.0f);
	const D3DXVECTOR3 InitTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	const float InitViewAngle = D3DXToRadian(60.0f);
	const float InitViewAspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	const float InitViewNear = 10.0f;
	const float InitViewFar = 50000.0f;

	transform.SetPosition(InitPos);
	target = InitTarget;
	viewAngle = InitViewAngle;
	viewAspect = InitViewAspect;
	viewNear = InitViewNear;
	viewFar = InitViewFar;

	D3DXMatrixIdentity(&viewport);
	viewport._11 = SCREEN_WIDTH / 2.0f;
	viewport._22 = -SCREEN_HEIGHT / 2.0f;
	viewport._41 = SCREEN_WIDTH / 2.0f;
	viewport._42 = SCREEN_HEIGHT / 2.0f;

	D3DXMatrixInverse(&invVPV, NULL, &VPV);

	Set();
}

/**************************************
�f�X�g���N�^
***************************************/
Camera::~Camera()
{
	
}

/**************************************
�X�V����
***************************************/
void Camera::Update()
{
	//�e�v���O�C���X�V
	for (auto& plugin : pluginList)
	{
		plugin->Update();
	}

	//��Ɨ̈�Ɍ��݂̃p�����[�^��ݒ�
	eyeWork = transform.GetPosition();
	targetWork = target;
	upWork = transform.Up();

	//�v���O�C�����f
	for (auto& plugin : pluginList)
	{
		plugin->Apply(*this);
	}

	//�r���[�s��쐬
	D3DXMatrixIdentity(&view);
	D3DXMatrixLookAtLH(&view,
		&eyeWork,
		&targetWork,
		&upWork);

	//�v���W�F�N�V�����s��쐬
	D3DXMatrixIdentity(&projection);
	D3DXMatrixPerspectiveFovLH(&projection,
		viewAngle,
		viewAspect,
		viewNear,
		viewFar);

	//�ϊ��s����v�Z
	VPV = view * projection * viewport;

	//�t�s����v�Z
	D3DXMatrixInverse(&invView, NULL, &view);
	D3DXMatrixInverse(&invProjection, NULL, &projection);
	D3DXMatrixInverse(&invVPV, NULL, &VPV);
}

/**************************************
�Z�b�g����
***************************************/
void Camera::Set()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�s��ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &view);

	//�v���W�F�N�V�����s��ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &projection);
}

/**************************************
�v���O�C���ǉ�����
***************************************/
void Camera::AddPlugin(BaseCameraPlugin * plugin)
{
	pluginList.push_back(plugin);
}

/**************************************
�v���O�C���폜����
***************************************/
void Camera::RemovePlugin(BaseCameraPlugin *plugin)
{
	pluginList.erase(std::remove(pluginList.begin(), pluginList.end(), plugin), pluginList.end());	
}

/**************************************
���C���J�����ݒ菈��
***************************************/
void Camera::SetMainCamera(Camera * camera)
{
	mainCamera = camera;
}

/**************************************
���C���J�����擾����
***************************************/
Camera * Camera::MainCamera()
{
	return mainCamera;
}

/**************************************
�X�N���[�����e����
***************************************/
void Camera::Projection(D3DXVECTOR3& out, const D3DXVECTOR3& pos)
{
	D3DXVec3TransformCoord(&out, &pos, &mainCamera->VPV);
}

/**************************************
�X�N���[���t���e����
***************************************/
void Camera::UnProjection(D3DXVECTOR3& out, const D3DXVECTOR3& pos, float z)
{
	D3DXVec3TransformCoord(&out, &D3DXVECTOR3(pos.x, pos.y, z), &mainCamera->invVPV);
}

/**************************************
�X�N���[���t���e����
***************************************/
D3DXMATRIX Camera::GetViewMtx()
{
	return mainCamera->view;
}

/**************************************
�X�N���[���t���e����
***************************************/
D3DXMATRIX Camera::GetInverseViewMtx()
{
	return mainCamera->invView;
}

/**************************************
�X�N���[���t���e����
***************************************/
D3DXMATRIX Camera::GetProjectionMtx()
{
	return mainCamera->projection;
}

