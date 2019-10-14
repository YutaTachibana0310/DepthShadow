//=====================================
//
//�J�����w�b�_[Camera.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../../main.h"

#include <vector>

class BaseCameraPlugin;
/**************************************
Camera�N���X
***************************************/
class Camera
{
	friend class BaseGame;
public:
	Camera();					//�R���X�g���N�^
	virtual ~Camera();			//�f�X�g���N�^

	virtual void Update();		//�X�V
	virtual void Set();			//�J������񔽉f����

	//�v���O�C���ǉ�����
	virtual void AddPlugin(BaseCameraPlugin* plugin);
	virtual void RemovePlugin(BaseCameraPlugin* plugin);

	//���C���J�����Z�b�g�A�Q�b�g����
	static void SetMainCamera(Camera* camera);
	static Camera* MainCamera();

	//�^�������[���h���W���X�N���[�����W�ɕϊ�����֐�
	void Projection(D3DXVECTOR3& out, const D3DXVECTOR3& pos);

	//�^�����X�N���[�����W�����[���h���W�ɕϊ�����֐�
	void UnProjection(D3DXVECTOR3& out, const D3DXVECTOR3& pos, float z);

	//�r���[�s��擾����
	D3DXMATRIX GetViewMtx();

	//�r���[�t�s��擾����
	D3DXMATRIX GetInverseViewMtx();

	//�v���W�F�N�V�����s��擾����
	D3DXMATRIX GetProjectionMtx();

protected:
	//SRT���
	Transform transform;

	//�����_
	D3DXVECTOR3 target;

	//���_�A�����_�A������i��Ɨp�̈�j
	D3DXVECTOR3 eyeWork;
	D3DXVECTOR3 targetWork;
	D3DXVECTOR3 upWork;

	//����p�A�A�X�y�N�g��A�j�A�l�A�t�@�[�l
	float viewAngle;
	float viewAspect;
	float viewNear;
	float viewFar;

	//�r���[�A�v���W�F�N�V�����s��A�r���[�|�[�g�s��
	D3DXMATRIX view, projection, viewport;
	D3DXMATRIX VPV;

	//�r���[�A�v���W�F�N�V�����A�r���[�|�[�g�t�s��
	D3DXMATRIX invView, invProjection, intViewport;
	D3DXMATRIX invVPV;

	//�v���O�C�����X�g
	std::vector<BaseCameraPlugin*> pluginList;
	
	//�Q�[���ɃZ�b�g�����J�����̃C���X�^���X
	static Camera* mainCamera;

public:
	//�J������h�炷�v���O�C��
	class ShakePlugin;
	
};

/**************************************
�J�����v���O�C�����N���X
***************************************/
class BaseCameraPlugin
{
public:
	virtual void Update() = 0;
	virtual void Apply(Camera& camera) = 0;
};

#endif