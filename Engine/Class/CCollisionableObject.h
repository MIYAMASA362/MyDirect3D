//
//	CCollisionableObject.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CCOLLISIONABLEOBJECT_H
#define CCOLLISIONABLEOBJECT_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include "CGameObject.h"

//================================================
//	マクロ定義	define
//================================================

#define Squared( a ) ( a * a ) // これ危険かも 要確認 ------CAUTION!>

//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================


//================================================
//	クラス		class
//================================================

/*
 * Shape Crustor
 */
class Shape
{
public:
	enum SHAPE_TYPE
	{
		SPHERE = 0,
		CUBOID,
		/* MAX ENUM */
		COLLISION_SHAPE_TYPE_ENUM_MAX
	};
public:
	SHAPE_TYPE ShapeType;
private:
	Shape(){}
public:
	Shape( SHAPE_TYPE ShapeType );
	virtual ~Shape();
};

//-------------------------------------
class ShapeSphere : public Shape
{
public:
	D3DXVECTOR3 Pos;
	float Radius;
public:
	ShapeSphere( D3DXVECTOR3 Pos, float Radius );
	ShapeSphere( float x, float y, float z, float Radius );
	~ShapeSphere();
};

//-------------------------------------
class ShapeCuboid : public Shape
{
public:
	D3DXVECTOR3 Pos; // 重心の座標
	D3DXVECTOR3 Length;
	D3DXVECTOR3 Angle;
public:
	ShapeCuboid( D3DXVECTOR3 Pos, D3DXVECTOR3 Length, D3DXVECTOR3 Radian );
	~ShapeCuboid();
};

/*
 * Collsion Class
 */

class Collision
{
private:
	
public:
	static bool SphereVsSphere( ShapeSphere& Sphere0, ShapeSphere& Sphere1 );
	static bool CuboidVsSphere(ShapeCuboid& Cuboid, ShapeSphere& Sphere) {};
	static bool CuboidVsCuboid(ShapeCuboid& Cuboid0, ShapeCuboid& Cuboid1) {};
};
//-------------------------------------
//	クラス名
//-------------------------------------

#endif