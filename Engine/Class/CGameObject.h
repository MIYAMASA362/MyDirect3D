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
//	GameObject�@�N���X
//===============================================
class GameObject
{
public:

private:
	static std::vector<GameObject*> pIndex;

public:
	static void g_Update();	//�S�̍X�V
	static void g_Render();	//�S�̕`��

public:
	Transform transform;	//�ʒu
	Render3D render;		//�`��

public:
	GameObject(Transform* pTransform);

	~GameObject();

public:
	void Set_Parent(GameObject* pParent);	//�e��ݒ�

public:
	virtual void Update();
	virtual void Render();
};

#endif // !GAMEOBJECT_H


