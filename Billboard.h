//
//	Billboard.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef BILLBOARD_H
#define BILLBOARD_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include<vector>

#include"CTransform.h"
#include"CAnimation.h"
#include"CTexture.h"

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
//	クラス
//================================================

//-------------------------------------
//	抽象クラス
//-------------------------------------
class ABillboard
{
public:
	static std::vector<ABillboard*> pIndex;
	static void g_Update();
	static void g_Render();

public:
	D3DXVECTOR3 Position;	//位置
	D3DXVECTOR3 Scale;		//大きさ

public:
	//コンストラクタ
	ABillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);
	~ABillboard();

public:
	virtual void Update() = 0;
	virtual void Render() = 0;
};

//-------------------------------------
//	Billboard
//-------------------------------------
class CBillboard:public ABillboard
{
public:
	
public:
	//コンストラクタ
	CBillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);

	//デストラクタ
	~CBillboard();

public:
	void Update() override;
	void Render() override;
};

//-------------------------------------
//	AnimationBillboard
//-------------------------------------
class AnimationBillboard:public ABillboard
{
public:
	Texture texture;
	Animation animation;
public:
	AnimationBillboard() :AnimationBillboard({ 0.0f,0.0f,0.0f }, {1.0f,1.0f,1.0f}) {};
	AnimationBillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);
	~AnimationBillboard();
public:
	void Update() final;
	void Render() final;
};

//================================================
//	関数		function
//================================================
void Billboard_Initialize();
void BillBoard_Create(D3DXVECTOR3 position);
void BillBoard_Create(Transform* pTransform);
void BillBoard_Finalaize();
void AnimaBillBoard_Create(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, Texture* pTexture, Animation* pAnimation);
void BillBoardShadow_Create(D3DXVECTOR3 Position, D3DXVECTOR3 Scale);
#endif