//
//	CBurst.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CBURST_H
#define CBURST_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include<vector>

//Class
#include"Billboard.h"

//================================================
//	マクロ定義	define
//================================================


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

//-------------------------------------
//	CBurst
//-------------------------------------
class CBurst
{
public:
	static std::vector<CBurst*> pIndex;
	static void g_Update();
	static void g_Render();
public:
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Scale;
	Texture texture;
	Animation animation;
public:
	CBurst(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);
	~CBurst();
public:
	void Update();
	void Render();
};

void Burst_Create(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);

#endif