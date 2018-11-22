//
//	Geometry.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/18
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#include"Geometry.h"
#include"System.h"

#include"Cube.h"
#include"Grid.h"
#include"MeshField_Ground.h"
#include"MeshField_Cylinder.h"
#include"MeshField_SkyDome.h"
//Class

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	グローバル変数	global
//===============================================


//===============================================
//	関数			function
//===============================================

//-------------------------------------
//	初期化
//-------------------------------------
void Geometry_Initialize()
{
	Cube_Initialize();
	Grid_Initialize();
	MeshField_Ground_Initialize();
	MeshCylinder_Initialize();
	MeshSkyDome_Initialize();
}

//-------------------------------------
//	更新
//-------------------------------------
void Geometry_Update()
{

}

//-------------------------------------
//	描画
//-------------------------------------
void Geometry_Render()
{
	Grid_Render();
}

//-------------------------------------
//	終了
//-------------------------------------
void Geometry_Finalize()
{
	MeshCylinder_Finalize();
	MeshField_Ground_Finalize();
	MeshSkyDome_Finalize();
}

