//
//	CGameObject.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/29
//===============================================
#include<d3dx9.h>
#include<vector>

#include"Cube.h"
#include"CGameObject.h"

//===============================================
//	グローバル変数
//===============================================
std::vector<GameObject*> GameObject::pIndex;

//===============================================
//	GameObject クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
GameObject::GameObject(Transform* pTransform)
{
	this->transform		= *pTransform;
	this->pIndex.push_back(this);
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
GameObject::~GameObject()
{

}

//-------------------------------------
//	親を設定
//-------------------------------------
void GameObject::Set_Parent(GameObject* pParent)
{
	this->transform.Set_Parent(&pParent->transform);
}

//------------------------------------
//	更新処理
//------------------------------------
void GameObject::Update()
{

}

//------------------------------------
//	描画処理
//------------------------------------
void GameObject::Render()
{
	render.Begin(&this->transform);
}

//===============================================
//	グローバル
//===============================================

//-----------------------------------
//	全体更新
//-----------------------------------
void GameObject::g_Update()
{
	for(int i = 0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->Update();
	}
}

//----------------------------------
//	全体描画
//----------------------------------
void GameObject::g_Render()
{
	for(int i = 0; i< pIndex.size(); i++)
	{
		pIndex.at(i)->Render();
	}
}
