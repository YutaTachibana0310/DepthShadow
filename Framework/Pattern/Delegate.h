//=====================================
//
// Delegate.h
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include <memory>

/**************************************
Delegater���N���X
***************************************/
template<class T>
class DelegateBase
{
public:
	DelegateBase() {}
	virtual ~DelegateBase() {}

	//int�^�����L��߂�l�����̊֐�
	virtual void operator()(T arg) = 0;
};

/**************************************
�^�G�C���A�X
***************************************/
template<class T>
using DelegatePtr = DelegateBase<T>*;

/**************************************
Delegater�N���X
***************************************/
template <class OBJ, class ARG>
class Delegate : public DelegateBase<ARG>
{
	typedef void(OBJ::*EventFunc)(ARG);
public:
	Delegate() :
		object(NULL), func(NULL) {}

	virtual ~Delegate() {}

	//�����Ȃ��߂�l�Ȃ��̊֐����s�̃I�y���[�^
	virtual void operator()(ARG arg)
	{
		//if (object != NULL && func != NULL)
			(object->*func)(arg);
	}

	//�I�u�W�F�N�g�Ɗ֐��̓o�^����
	void Set(OBJ* object, EventFunc func)
	{
		this->object = object;
		this->func = func;
	}

	//�f���Q�[�^�쐬����
	static DelegatePtr<ARG> Create(OBJ* object, void (OBJ::*func)(ARG))
	{
		Delegate<OBJ, ARG>* delegate = new Delegate<OBJ, ARG>;
		delegate->Set(object, func);
		return  delegate;
	}

protected:
	OBJ* object;			//�I�u�W�F�N�g
	EventFunc func;			//�֐��|�C���^
};

#endif
