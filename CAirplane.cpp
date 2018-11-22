//
//	CAirplane.cpp
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include<d3dx9.h>

//class
#include"CAirplane.h"
#include"input.h"

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================


//===============================================
//	CAirplane
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
CAirplane::CAirplane(Transform* pTransform)
:
	GameObject(pTransform),
	Propeller(		&Transform({ 0.0f,0.0f,-60.0f })),
	WingRight_Up(&Transform({ -302.0f,85.0f,68.0f })),
	WingRight_Down(	&Transform({ -264.0f,-11.0f,95.0f })),
	WingLeft_Up(	&Transform({ 302.0f,85.0f,68.0f })),
	WingLeft_Down(	&Transform({ 264.0f,-11.0f,95.0f })),
	WingBack_Up(&Transform({ 0.0f,33.0f,358.0f})),
	WingBack_Down(&Transform({0.0f,21.0f,346.0f})),
	camera(D3DXVECTOR3(0.0f,40.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,-10.0f)),
	Cockpit(D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,-1.0f))
{
	Speed =  Propeller_Speed = 0.0f;
	
	//�e�q�֌W�̐ݒ�
	this->camera.transform.Set_Parent(&this->transform);
	this->Cockpit.transform.Set_Parent(&this->transform);

	this->Propeller		.Set_Parent(this);
	this->WingRight_Up	.Set_Parent(this);
	this->WingRight_Down.Set_Parent(this);
	this->WingLeft_Up	.Set_Parent(this);
	this->WingLeft_Down	.Set_Parent(this);
	this->WingBack_Up	.Set_Parent(this);
	this->WingBack_Down	.Set_Parent(this);

	//���f���̐ݒ�
	this->render.SetMesh(new CXModelName(XModel::AIRPLANE_BODY));
	this->Propeller.render.SetMesh(new CXModelName(XModel::AIRPLANE_PROPELLER));
	this->WingRight_Up.render.SetMesh(new CXModelName(XModel::AIRPLANE_WingRU));
	this->WingRight_Down.render.SetMesh(new CXModelName(XModel::AIRPLANE_WingRD));
	this->WingLeft_Up.render.SetMesh(new CXModelName(XModel::AIRPLANE_WingLU));
	this->WingLeft_Down.render.SetMesh(new CXModelName(XModel::AIRPLANE_WingLD));
	this->WingBack_Up.render.SetMesh(new CXModelName(XModel::AIRPLANE_WingBU));
	this->WingBack_Down.render.SetMesh(new CXModelName(XModel::AIRPLANE_WingBD));

}

//========================================
//	�J����
//========================================

//-------------------------------------
//	��荞��
//-------------------------------------
void CAirplane::Boarding()
{
	this->camera.Set_Main();
}

//-------------------------------------
//	�J�����؂�ւ�
//-------------------------------------
void CAirplane::Change()
{
	if(ACamera::Get_Main() == &this->camera)
	{
		this->Cockpit.Set_Main();
	}
	else if(ACamera::Get_Main() == &this->Cockpit)
	{
		this->camera.Set_Main();
	}

}

//========================================
//	����
//========================================

//-------------------------------------
//	�O�i
//-------------------------------------
void CAirplane::Advance()
{
	Speed += AIRPLANE_ADVANCE_SPEED;
	Propeller_Speed += AIRPLANE_ADVANCE_SPEED * 2.0f;
}

//-------------------------------------
//	�X�V����
//-------------------------------------
void CAirplane::Update()
{
	camera.Update();
	Cockpit.Update();
	Propeller.transform.rotation.z += D3DXToRadian(50);
}
