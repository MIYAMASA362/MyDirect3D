//
//	Transform.cpp
//		Author:HIROMASA IKEDA	DATA:2018/11/22
//===============================================
#include<d3dx9.h>
#include"CTransform.h"

//===============================================
//	�O���[�o���ϐ�
//===============================================
std::vector<Transform*> Transform::pIndex;

//===============================================
//	ATransform
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
ATransform::ATransform()
{

}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
ATransform::~ATransform()
{
	
}

//===============================================
//	BasicTransform
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
BasicTransform::BasicTransform()
{

}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
BasicTransform::~BasicTransform()
{

}

//===============================================
//	Transform
//===============================================

//-------------------------------------
//	�ĕϊ����\
//-------------------------------------
void Transform::ConvertReset()
{
	for(int i = 0; i < pIndex.size();i++)
	{
		pIndex.at(i)->bConverted = false;	//Window�ŃG���[���N���錴�����ۂ�
	}
}

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Transform::Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation)
{
	this->bConverted = false;
	this->pParent = NULL;

	//���[���h���
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;

	//���[�J�����
	this->position = Position;
	this->scale = Scale;
	this->rotation = Rotation;

	this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3Normalize(&this->forward, &this->forward);
	D3DXVec3Cross(&this->right, &this->forward, &this->up);
	D3DXVec3Normalize(&this->right, &this->right);

	pIndex.push_back(this);
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
Transform::~Transform()
{
	this->pParent = NULL;

	//�q�������Ă���Ȃ�
	if (this->pChild.size() > 0)
	{
		for (int i = 0; i < this->pChild.size(); i--)
		{
			//�q�ɐe�̎��S��`����
			this->pChild.at(i)->Release_Parent();
		}
	}

	this->pChild.clear();
}

//-------------------------------------
//	�e��ݒ�
//-------------------------------------
void Transform::Set_Parent(Transform* pParent)
{
	this->pParent = pParent;
	pParent->pChild.push_back(this);	//�e�Ɏq���o��������

	this->Position = pParent->Position + this->position;
	this->Scale = pParent->Scale + this->scale;
	this->Rotation = pParent->Rotation + this->rotation;

}

//-------------------------------------
//	�����X�V
//-------------------------------------
Transform* Transform::Set_UpdateTransform()
{
	if (this->pParent != NULL)
	{
		this->Position = pParent->Position + this->position;
		this->Scale = pParent->Scale + this->scale;
		this->Rotation = pParent->Rotation + this->rotation;
	}
	else
	{
		this->Position = this->position;
		this->Rotation = this->rotation;
		this->Scale = this->scale;
	}

	return this;
}

//-------------------------------------
//	�e���擾
//-------------------------------------	
Transform* Transform::Get_Parent()
{
	return this->pParent;
}

//-------------------------------------
//	�s��ϊ�
//-------------------------------------
D3DXMATRIX Transform::Convert()
{
	this->bConverted = false;
	this->Set_UpdateTransform();
	if (this->bConverted) return this->MtxWorld;	//��x�ϊ�����Ă���

	//�e�s��
	D3DXMATRIX MtxTransform;	//�ʒu
	D3DXMATRIX MtxScale;		//�傫��
	D3DXMATRIX MtxRotation;		//��]

	//�s��ϊ�
	D3DXMatrixTranslation(&MtxTransform, this->position.x, this->position.y, this->position.z);
	D3DXMatrixScaling(&MtxScale, this->scale.x, this->scale.y, this->scale.z);
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->rotation.y, this->rotation.x, this->rotation.z);

	//����
	this->up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXVec3TransformNormal(&this->up,&this->up,&MtxRotation);
	D3DXVec3Normalize(&this->up, &this->up);

	//�O���
	this->forward = D3DXVECTOR3(0.0f,0.0f,1.0f);
	D3DXVec3TransformNormal(&this->forward,&this->forward,&MtxRotation);
	D3DXVec3Normalize(&this->forward, &this->forward);

	//�E���
	D3DXVec3Cross(&this->right, &this->up, &this->forward);

	//���[���h�s��̍쐬
	D3DXMatrixIdentity(&this->MtxWorld);
	this->MtxWorld = MtxScale * MtxRotation * MtxTransform;

	//�e������
	if (this->pParent != NULL)
	{
		//�e�̍s�񌩂Ă���
		this->MtxWorld *= this->pParent->Convert();
	}

	//�ϊ��I��	
	this->bConverted = true;

	return this->MtxWorld;
}

//-------------------------------------
//	�e�����
//-------------------------------------
void Transform::Release_Parent()
{
	this->pParent = NULL;
}

//===============================================
//	Transform2
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Transform2::Transform2()
{
	Position = { 0.0f,0.0f };
	Scale = { 1.0f,1.0f };
	Rotation = 0;
	Color = Color;
}

Transform2::Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation)
{
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;
	Color = D3DCOLOR_RGBA(255, 255, 255, 255);
}

Transform2::Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation, D3DCOLOR Color)
{
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;
	this->Color = Color;
}
