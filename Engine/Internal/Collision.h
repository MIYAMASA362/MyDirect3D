//
//	Collision.h
//		Author:HIROMASA IKEDA		DATE:2018/06/26
//===============================================
//
//	使ってない
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
//	あたり判定構造体
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
//	Collision クラス
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
	Transform2* pTransform2;	//親位置
	
	D3DXVECTOR2 Force;			//力
	D3DXVECTOR2 velocity;		//速度

	bool UseGravity;				//重力を使う
	void Update(float Speed);		//更新処理
	void Update(D3DXVECTOR2 Speed);	//更新処理
	HIT_PORTION Collision_Hit(const Collision* pCollision);	//あたり判定

	Physics();
};

//***********************************************
//	プロトタイプ宣言
//***********************************************
bool Collision_Hit(const Circle *pCircle_A, const Circle *pCircle_B);
bool Collision_Hit(const Circle *pCircle_A, const Box *pBox_B);
bool Collision_Hit(const Box *pBox_A, const Box *pBox_B);

#endif

