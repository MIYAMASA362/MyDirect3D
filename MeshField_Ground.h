//
//	MeshField_Ground.h
//		Author:HIROMASA IKEDA	DATE:2018/10/25
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef MESHFIELD_GROUND_H
#define MESHFIELD_GROUND_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include"Texture.h"

//================================================
//	マクロ定義	define
//================================================
#define MESHFIELD_GRIDNUM_WIDTH (50)		//グリッド幅数(四角ポリゴン数)
#define MESHFIELD_GRIDNUM_DEPTH (50)		//グリッド奥行き数(四角ポリゴン数)

#define MESHFIELD_SIZE_WIDTH (100)			//サイズ幅
#define MESHFIELD_SIZE_DEPTH (100)			//サイズ奥行き

//頂点系
#define FVF_MESHFIELD_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================
struct MeshFieldVertex3D
{
	D3DXVECTOR3 Position;	//位置
	D3DXVECTOR3 Normal;		//法線
	D3DCOLOR Color;			//色
	D3DXVECTOR2 TexCoord;	//テクスチャ
};

//================================================
//	グローバル変数　global
//================================================


//================================================
//	関数		function
//================================================
void MeshField_Ground_Initialize();
void MeshField_Ground_Render(const D3DXVECTOR3 Center, TEXTURE_NAME Texture);
void MeshField_Ground_Finalize();



#endif