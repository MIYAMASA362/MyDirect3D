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

#endif