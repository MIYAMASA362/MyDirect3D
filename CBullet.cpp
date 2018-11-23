//
//	CBullet.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/22
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#include"CBullet.h"

//class
#include"Billboard.h"
#include"CBurst.h"

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	グローバル変数	global
//===============================================
std::vector<CBullet*> CBullet::pIndex;
float CBullet::Speed = 2.0f;

//===============================================
//	CBullet
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CBullet::CBullet(D3DXVECTOR3 Position,D3DXVECTOR3 Scale,D3DXVECTOR3 face)
:
	transform(Position,Scale)
{
	this->CreatePosition = Position;
	this->face = face;
	pIndex.push_back(this);
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CBullet::~CBullet()
{
	std::vector<CBullet*>::iterator me = pIndex.begin();

	while(me != pIndex.end())
	{
		if((*me) == this)
		{
			me = pIndex.erase(me);
			break;
		}
		me++;
	}
}

//-------------------------------------
//	更新処理
//-------------------------------------
void CBullet::Update()
{
	this->transform.Position += this->face * Speed;
	//this->transform.Position.y -= 0.2f;	//弾の落下
	if(this->transform.Position.y <= 0.0f)
	{
		this->Destroy();
	}
	
	D3DXVECTOR3 VecDis = this->CreatePosition - this->transform.Position;
	if (D3DXVec3Length(&VecDis) >= 100)
	{
		this->~CBullet();
	}

}

//-------------------------------------
//	描画処理
//-------------------------------------
void CBullet::Render()
{
	BillBoard_Create(&this->transform);
}

//-------------------------------------
//	削除
//-------------------------------------
void CBullet::Destroy()
{
	Burst_Create(this->transform.Position, { 4.0f,4.0f,4.0f });
	this->~CBullet();
}

//=====================================
//	グローバル関数
//=====================================

//-------------------------------------
//	更新
//-------------------------------------
void CBullet::g_Update()
{
	for(int i =0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->Update();
	}
}

//-------------------------------------
//	描画
//-------------------------------------
void CBullet::g_Render()
{
	for (int i = 0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->Render();
	}
}

//===============================================
//	関数
//===============================================

void CBullet_Create(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 face)
{
	CBullet* bullet = new CBullet(Position,Scale,face);
}

//-------------------------------------
//	終了処理
//-------------------------------------
void CBullet_Finalize()	
{
	/*
	//全要素を削除したい
	std::vector<CBullet*>::iterator it = CBullet::pIndex.end();
	while(it != CBullet::pIndex.begin())
	{
		delete *it;
		it--;
	}
	*/
	CBullet::pIndex.clear();
}
