//
//	Texture.h
//		Auther:HIROMASA IKEDA	Date:2018/09/13
//===============================================
#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include<d3dx9.h>
#include"common.h"

//===============================================
//	マクロ定義
//===============================================
#define TEXTURE_FILENAME_MAX (64)

//===============================================
//	列挙
//===============================================

//-------------------------------------
//	テクスチャ名リスト
//-------------------------------------
typedef enum TEXTURE_NAME
{
	CubeTexture,
	BillBoardTex,
	MeshFieldTex,
	MeshCylinderTex,
	TEXTURE_NAME_END,	//テクスチャ終わり
	TEXTURE_NONE		//指定無い場合
}TEXTURE_NAME;

//===============================================
//	構造体
//===============================================

//-------------------------------------
//	TexScale
//-------------------------------------
typedef struct TEXSCALE
{
	int width;
	int height;
}TEXSCALE;

//-------------------------------------
//	TexCoord
//-------------------------------------
typedef struct TEXCOORD
{
	int x;
	int y;
}TEXCOORD;

//===============================================
//	関数
//===============================================

void Texture_Initialize();							//テクスチャ初期化
void Texture_Finalize();							//テクスチャ終了

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index);	//テクスチャポインタ取得
int Texture_GetWidth(int index);					//テクスチャ幅取得 
int Texture_GetHeight(int index);					//テクスチャ高さ取得

#endif
