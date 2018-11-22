//
//	CTexture.h
//		Author:HIROMASA IKEDA	DATE:2018/11/22
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
	//==============================================
	//	列挙型
	//==============================================

	const enum Name
	{
		NAME_END,	//テクスチャ最終番目
		NONE		//指定なし
	};

	//==============================================
	//	構造体
	//==============================================
	
	struct Data
	{
		LPDIRECT3DTEXTURE9 texture;	//テクスチャ
		UINT width;					//幅
		UINT height;				//高さ
	};

	struct Path
	{
		Name name;					//テクスチャ名
		const char Address[60];		//ファイルアドレス
	};

	//==============================================
	//	グローバル変数
	//==============================================

	static Path path[] =
	{
		{NONE,""}
	};

	//==============================================
	//	クラス
	//==============================================

	//-------------------------------------
	//	抽象クラス
	//-------------------------------------
	class ATexture
	{
	public:
		Name name;			//テクスチャ名
		D3DXVECTOR2 Coord;	//座標(左上)
		D3DXVECTOR2 Scale;	//サイズ
	public:
		ATexture();
	};

	//------------------------------------
	//	テクスチャクラス
	//------------------------------------
	class CTexture :public ATexture
	{
	public:

	public:
		CTexture();
	};

	//==============================================
	//	関数
	//==============================================
	void Load();
	void Finalize();
	LPDIRECT3DTEXTURE9 Get(Name name);
	UINT Get_Width(Name name);
	UINT Get_Height(Name name);
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

