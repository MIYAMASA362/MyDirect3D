//
//	CCollisionableObject.cpp
//		Author:HASHIMOTO	DATE:2018/10/19
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"

//class
#include "CCollisionableObject.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================


//===============================================
//	Shape クラス
//===============================================
Shape::Shape( SHAPE_TYPE init_ShapeType )
{
	ShapeType = init_ShapeType;
}
Shape::~Shape()
{
	// null
}

//===============================================
//	ShapeSphere クラス
//===============================================

//-------------------------------------
//  コンストラクタ デストラクタ
//-------------------------------------

ShapeSphere::ShapeSphere( D3DXVECTOR3 init_Pos, float init_Radius )
	: Shape( SHAPE_TYPE::SPHERE ), 
	Pos( init_Pos ), Radius( init_Radius )
{
	
}
ShapeSphere::ShapeSphere( float init_x, float init_y, float init_z, float init_Radius )
	: Shape( SHAPE_TYPE::SPHERE ), 
	Pos( init_x, init_y, init_z ), Radius( init_Radius )
{

}
ShapeSphere::~ShapeSphere()
{
	// null
}

//===============================================
//	ShapeCuboid クラス
//===============================================

//-------------------------------------
//  コンストラクタ デストラクタ
//-------------------------------------

ShapeCuboid::ShapeCuboid( D3DXVECTOR3 init_Pos, D3DXVECTOR3 init_Length, D3DXVECTOR3 init_Radian )
	: Shape( SHAPE_TYPE::CUBOID ),
	Pos( init_Pos ), Length( init_Length ), Angle( init_Radian )
{

}

ShapeCuboid::~ShapeCuboid()
{
	// null
}

//===============================================
//	Collision クラス
//===============================================


bool Collision::SphereVsSphere( ShapeSphere& Sphere0, ShapeSphere& Sphere1 )
{
	D3DXVECTOR3 vecLength = Sphere1.Pos - Sphere0.Pos;
	FLOAT fLength = D3DXVec3Length(&vecLength);
	if( ( Sphere0.Radius + Sphere1.Radius )> fLength)
	{ // hit 
		return true;
	}
	else
	{ // no hit
		return false;
	}
}