//
//	Transform.h
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<d3dx9.h>
#include<vector>

//===============================================
//	Transform : 3D��p�@�N���X
//===============================================
class Transform
{
public:
	static std::vector<Transform*> pIndex;	//Transform�z��

public:
	static void ConvertReset();			//�ĕϊ����\��

private:
	Transform* pParent;					//�e
	std::vector<Transform*> pChild;		//�q
	D3DXMATRIX MtxWorld;				//���g�̕ϊ��s��

public :
	bool bConverted;					//�ϊ�������

	//���[���h���
	D3DXVECTOR3 Position;	//�EWorld Position	(pParent->Position + this->position)
	D3DXVECTOR3 Scale;		//�EWorld Scale		(pParent->Scale + this->scale)
	D3DXVECTOR3 Rotation;	//�EWorld Rotation	(pParent->Rotation + this->rotation)
	
	//���[�J�����
	D3DXVECTOR3 position;	//�Elocal Position �ʒu
	D3DXVECTOR3 scale;		//�Elocal Scale �T�C�Y
	D3DXVECTOR3 rotation;	//�Elocal Rotation ��]

	//������
	D3DXVECTOR3 up;			//�E��
	D3DXVECTOR3 forward;	//�E�O
	D3DXVECTOR3 right;		//�E�E

public:
	//�R���X�g���N�^
	Transform() :Transform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }){};
	Transform(D3DXVECTOR3 Position) :Transform(Position, { 1.0f,1.0f,1.0f }, {0.0f,0.0f,0.0f}) {};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale) :Transform(Position, Scale, { 0.0f,0.0f,0.0f }) {};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation);

	~Transform();
	
public:
	D3DXMATRIX Convert();	//�s��ϊ��J�n
	void Release_Parent();					//�e�����

public:
	//SET�֐�
	void Set_Parent(Transform* pParent);	//�e��ݒ�
	Transform* Set_UpdateTransform();		//�����X�V����		
public:
	//GET�֐�
	Transform* Get_Parent();				//�e���擾
};

//===============================================
//	Transform2 : 2D��p�@�N���X
//===============================================
class Transform2
{
private:

public:
	D3DXVECTOR2 Position;	//�ʒu
	D3DXVECTOR2 Scale;		//�T�C�Y
	float Rotation;			//��]
	D3DCOLOR Color;			//�F

	//�R���X�g���N�^
	Transform2();
	Transform2(D3DXVECTOR2 Position,D3DXVECTOR2 Scale,float Rotation);
	Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation,D3DCOLOR Color);
	
};

#endif
