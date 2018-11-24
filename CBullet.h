//
//	CBullet.h
//		Author:HIROMASA IKEDA	DATE:2018/11/22
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CBULLET_H
#define CBULLET_H

//================================================
//	インクルード	include
//================================================
#include<d3dx9.h>
#include<vector>
#include"common.h"

#include"CTransform.h"
//Class

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
//	CBullet
//-------------------------------------
class CBullet
{
public:
	static std::vector<CBullet*> pIndex;

public:
	static void g_Update();
	static void g_Render();

public:
	static float Speed;			//弾速

private:
	D3DXVECTOR3 CreatePosition;
	D3DXVECTOR3 face;

public:
	Transform transform;	//位置情報

public:
	//コンストラクタ
	CBullet(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 face);

	//デストラクタ
	~CBullet();

public:
	void Update();			//更新
	void Render();			//描画

	void Destroy();			//削除
};

void CBullet_Create(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 face);
void CBullet_Finalize();

#endif