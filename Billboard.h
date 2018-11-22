//
//	Billboard.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef BILLBOARD_H
#define BILLBOARD_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>

#include"CTransform.h"
#include"CAnimation.h"
#include"CTexture.h"

//================================================
//	�}�N����`	define
//================================================


//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�N���X
//================================================

//-------------------------------------
//	���ۃN���X
//-------------------------------------
class ABillboard
{
public:
	D3DXVECTOR3 Position;	//�ʒu
	D3DXVECTOR3 Scale;		//�傫��

public:
	//�R���X�g���N�^
	ABillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);
	~ABillboard();

public:
	virtual void Update() = 0;
	virtual void Render() = 0;
};

//-------------------------------------
//	Billboard
//-------------------------------------
class CBillboard:public ABillboard
{
public:
	
public:
	//�R���X�g���N�^
	CBillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);

	//�f�X�g���N�^
	~CBillboard();

public:
	void Update() override;
	void Render() override;
};

//-------------------------------------
//	AnimationBillboard
//-------------------------------------
class AnimationBillboard:public ABillboard
{
public:
	Texture texture;
	Animation animation;
public:
	AnimationBillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);
	~AnimationBillboard();
public:
	void Update() override;
	void Render() override;
};

//================================================
//	�֐�		function
//================================================
void Billboard_Initialize();
void BillBoard_Create(D3DXVECTOR3 position);
void BillBoard_Create(Transform* pTransform);
void BillBoard_Finalaize();

#endif