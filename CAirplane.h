//
//	CAirplane.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CAIRPLANE_H
#define CAIRPLANE_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include<d3dx9.h>
#include"CGameObject.h"
#include"CCamera.h"

//================================================
//	マクロ定義	define
//================================================
#define AIRPLANE_ADVANCE_SPEED (0.0025f)
#define AIRPLANE_MAX_PROPELLER_SPEEFD (2.0f)

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
//	Airplane
//-------------------------------------
class CAirplane :public GameObject
{
	
private:
	//パーツ群
	GameObject Propeller;
	GameObject WingRight_Up;
	GameObject WingRight_Down;
	GameObject WingLeft_Up;
	GameObject WingLeft_Down;
	GameObject WingBack_Up;
	GameObject WingBack_Down;

private:
	Camera camera;
	Camera Cockpit;			//操縦席

public:
	float Speed;
	float Propeller_Speed;
public:
	CAirplane(Transform* pTransform);

public:	//カメラ
	
	void Boarding();	//乗り込む
	void Change();		//切り替え

public:
	//動き系
	void Advance();		//前進
	

public:
	void Update();
};

#endif