//
//	MeshField_Cylinder.h
//		Author:IKEDA HIROMASA	DATE:2018/11/12
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef MESHFIELD_CYLINDER_H
#define MESHFIELD_CYLINDER_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>

#include"Texture.h"

//================================================
//	マクロ定義	define
//================================================
#define FVF_MESHFIELD (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

#define MESH_CYLINDER_HEIGHT (50)	//高さ
#define MESH_CYLINDER_RADIUS (40.0f)	//半径

#define MESH_CYLINDER_GRID_WIDTH (100)	//横グリッド数
#define MESH_CYLINDER_GRID_HEIGHT (10)	//縦グリッド数

#define MESH_ANGLE ((2*M_PI)/MESH_CYLINDER_GRID_WIDTH)	//1グリッド角度
#define MESH_HEIGHT (MESH_CYLINDER_HEIGHT / MESH_CYLINDER_GRID_HEIGHT)	//1グリッド高さ


//================================================
//	列挙型		enum
//================================================
struct  MeshFieldVertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR2 TexCoord;
};

//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================


//================================================
//	関数		function
//================================================
void MeshCylinder_Initialize();
void MeshCylinder_Render(const D3DXVECTOR3 Center, TEXTURE_NAME Texture);
void MeshCylinder_Finalize();
D3DXVECTOR3 MeshCylinder_GetCenter();
#endif