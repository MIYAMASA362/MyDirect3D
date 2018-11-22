//
//	Collision.h
//		Author:HIROMASA IKEDA		DATE:2018/06/26
//===============================================
//
//	�g���ĂȂ�
//
//-----------------------------------------------
#pragma once

#ifndef COLLISION_H
#define COLLISION_H

#include<d3dx9.h>
#include<vector>
#include"Texture.h"
#include"CTransform.h"

using namespace std;

typedef struct SCALE
{
	float width;
	float height;
}SCALE;

//===============================================
//	�����蔻��\����
//===============================================
typedef struct Box
{
	D3DXVECTOR2 Center;
	SCALE Scale;
}Box;


typedef struct Circle
{
	D3DXVECTOR2 Center;
	float radius;
}Circle;

typedef enum HIT_PORTION
{
	NONE,
	TOP,
	BOTTOM,
	RIGHT,
	LEFT,
	HIT
}HIT_PORTION;

//===============================================
//	Collision �N���X
//===============================================
class Collision
{
private:
	
public :
	vector<Box*> BoxIndex;
	bool trigger;
	Collision();
};

//===============================================
//	Physics
//===============================================
class Physics
{
private:
	
public:
	Collision* pCollision;
	Transform2* pTransform2;	//�e�ʒu
	
	D3DXVECTOR2 Force;			//��
	D3DXVECTOR2 velocity;		//���x

	bool UseGravity;				//�d�͂��g��
	void Update(float Speed);		//�X�V����
	void Update(D3DXVECTOR2 Speed);	//�X�V����
	HIT_PORTION Collision_Hit(const Collision* pCollision);	//�����蔻��

	Physics();
};

//***********************************************
//	�v���g�^�C�v�錾
//***********************************************
bool Collision_Hit(const Circle *pCircle_A, const Circle *pCircle_B);
bool Collision_Hit(const Circle *pCircle_A, const Box *pBox_B);
bool Collision_Hit(const Box *pBox_A, const Box *pBox_B);

#endif

