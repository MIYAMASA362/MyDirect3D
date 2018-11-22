//
//	CTexture.h
//		Author:HIROMASA IKEDA	DATE:2018/09/26
//===============================================
#pragma once
#ifndef CTEXTURE_H
#define CTEXTURE_H

#include<d3dx9.h>
#include"Texture.h"

//===============================================
//	Class	クラス
//===============================================

namespace TEXTURE
{
	//-------------------------------------
	//	抽象クラス
	//-------------------------------------
	class ATexture
	{
	public:
		ATexture();
	};
}

//-------------------------------------
//	テクスチャ
//-------------------------------------
class Texture
{
private:
	int Tex_Width;				//元テクスチャの幅
	int Tex_Height;				//元テクスチャの高さ
public:
	int Texture_index;			//テクスチャ名
	TEXCOORD TexCoord;			//テクスチャ座標
	TEXSCALE TexScale;			//テクスチャサイズ

	int GetWidth();				//幅取得
	int GetHeight();			//高さ取得
	TEXSCALE GetTexScale();		//サイズ取得

public:
	//コンストラクタ
	Texture():Texture(TEXTURE_NONE, { 0,0 }, { 0,0 }){};
	Texture(int Texture_index, TEXCOORD TexCoord, TEXSCALE TexScale);
};


#endif // !CTEXTURE_H

