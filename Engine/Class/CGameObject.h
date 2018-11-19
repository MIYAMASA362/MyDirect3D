//
//	GameObject.h
//		Author:HIROMASA IKEDA	DATE:2018/09/30
//===============================================
#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<d3dx9.h>
#include<vector>

//Class
#include"CTransform.h"
#include"CRender.h"
#include"Component.h"

#include"XModel.h"

//===============================================
//	GameObject　クラス
//===============================================
class GameObject
{
public:

private:
	static std::vector<GameObject*> pIndex;

public:
	static void g_Update();	//全体更新
	static void g_Render();	//全体描画

public:
	Transform transform;	//位置
	Render3D render;		//描画

public:
	GameObject(Transform* pTransform);

	~GameObject();

public:
	void Set_Parent(GameObject* pParent);	//親を設定

public:
	virtual void Update();
	virtual void Render();
};

#endif // !GAMEOBJECT_H


