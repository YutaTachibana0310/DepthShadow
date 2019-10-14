//=============================================================================
//
// ���͏��� [input.cpp]
// Author : 
//
//=============================================================================
#include "input.h"

namespace Input
{
	//*****************************************************************************
	// �O���[�o���ϐ�
	//*****************************************************************************
	LPDIRECTINPUT8 pDInput = NULL;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^

	//=============================================================================
	// ���͏����̏�����
	//=============================================================================
	HRESULT Init(HINSTANCE hInst, HWND hWnd)
	{
		HRESULT hr;

		if(!pDInput)
		{
			// DirectInput�I�u�W�F�N�g�̍쐬
			hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
				IID_IDirectInput8, (void**)&pDInput, NULL);
		}

		// �L�[�{�[�h�̏�����
		Keyboard::Init(hInst, hWnd, pDInput);

		//�}�E�X������
		Mouse::Init(hInst, hWnd, pDInput);

		//�p�b�h����������
		GamePad::Init(pDInput);

		return S_OK;
	}

	//=============================================================================
	// ���͏����̏I������
	//=============================================================================
	void Uninit()
	{
		// �L�[�{�[�h�̏I������
		Keyboard::Uninit();

		//�}�E�X�I������
		Mouse::Uninit();

		//�p�b�h�I������
		GamePad::Uninit();

		if (pDInput)
		{// DirectInput�I�u�W�F�N�g�̊J��
			pDInput->Release();
			pDInput = NULL;
		}
	}

	//=============================================================================
	// ���͏����̍X�V����
	//=============================================================================
	void Update(void)
	{
		// �L�[�{�[�h�̍X�V
		Keyboard::Update();

		//�}�E�X�X�V����
		Mouse::Update();

		//�Q�[���p�b�h�X�V����
		GamePad::Update();
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetPressHorizontail(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetPress(DIK_LEFT) || GamePad::GetPress(0, BUTTON_LEFT) || GamePad::GetPressPOV(0, POV_LEFT))
				return -1.0f;

			if (Keyboard::GetPress(DIK_RIGHT) || GamePad::GetPress(0, BUTTON_RIGHT) || GamePad::GetPressPOV(0, POV_RIGHT))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetPress(no, BUTTON_LEFT) || GamePad::GetPressPOV(no, POV_LEFT))
				return -1.0f;

			if (GamePad::GetPress(no, BUTTON_RIGHT) || GamePad::GetPressPOV(no, POV_RIGHT))
				return 1.0f;

			return 0.0f;
		}
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetPressVertical(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetPress(DIK_DOWN) || GamePad::GetPress(0, BUTTON_DOWN) || GamePad::GetPressPOV(0, POV_DOWN))
				return -1.0f;

			if (Keyboard::GetPress(DIK_UP) || GamePad::GetPress(0, BUTTON_UP) || GamePad::GetPressPOV(0, POV_UP))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetPress(no, BUTTON_DOWN) || GamePad::GetPress(no, POV_DOWN))
				return -1.0f;

			if (GamePad::GetPress(no, BUTTON_UP) || GamePad::GetPress(no, POV_UP))
				return 1.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetTriggerHorizontal(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetTrigger(DIK_LEFT) || GamePad::GetTrigger(0, BUTTON_LEFT) || GamePad::GetTriggerPOV(0, POV_LEFT))
				return -1.0f;

			if (Keyboard::GetTrigger(DIK_RIGHT) || GamePad::GetTrigger(0, BUTTON_RIGHT) || GamePad::GetTriggerPOV(0, POV_RIGHT))
				return 1.0f;
		}
		else
		{
			if (GamePad::GetTrigger(no, BUTTON_LEFT) || GamePad::GetTriggerPOV(no, POV_LEFT))
				return -1.0f;

			if (GamePad::GetTrigger(no, BUTTON_RIGHT) || GamePad::GetTriggerPOV(no, POV_RIGHT))
				return 1.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetTriggerVertical(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetTrigger(DIK_DOWN) || GamePad::GetTrigger(0, BUTTON_DOWN) || GamePad::GetTriggerPOV(0, POV_DOWN))
				return -1.0f;

			if (Keyboard::GetTrigger(DIK_UP) || GamePad::GetTrigger(0, BUTTON_UP) || GamePad::GetTriggerPOV(0, POV_UP))
				return 1.0f;
		}
		else
		{
			if (GamePad::GetTrigger(no, BUTTON_DOWN) || GamePad::GetTriggerPOV(no, POV_DOWN))
				return -1.0f;

			if (GamePad::GetTrigger(no, BUTTON_UP) || GamePad::GetTriggerPOV(no, POV_UP))
				return 1.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetRepeatHorizontal(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetRepeat(DIK_LEFT) || GamePad::GetRepeat(0, BUTTON_LEFT) || GamePad::GetRepeatPOV(0, POV_LEFT))
				return -1.0f;

			if (Keyboard::GetRepeat(DIK_RIGHT) || GamePad::GetRepeat(0, BUTTON_RIGHT) || GamePad::GetRepeatPOV(0, POV_RIGHT))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetRepeat(no, BUTTON_LEFT) || GamePad::GetRepeatPOV(no, POV_LEFT))
				return -1.0f;

			if (GamePad::GetRepeat(no, BUTTON_RIGHT) || GamePad::GetRepeatPOV(no, POV_RIGHT))
				return 1.0f;

			return 0.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetRepeatVertical(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetRepeat(DIK_DOWN) || GamePad::GetRepeat(no, BUTTON_DOWN) || GamePad::GetRepeatPOV(no, POV_DOWN))
				return -1.0f;
			
			if (Keyboard::GetRepeat(DIK_UP) || GamePad::GetRepeat(no, BUTTON_UP) || GamePad::GetRepeatPOV(no, POV_UP))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetRepeat(no, BUTTON_DOWN) || GamePad::GetRepeatPOV(no, POV_DOWN))
				return -1.0f;

			if (GamePad::GetRepeat(no, BUTTON_UP) || GamePad::GetRepeatPOV(no, POV_UP))
				return 1.0f;
		}

		return 0.0f;
	}
}