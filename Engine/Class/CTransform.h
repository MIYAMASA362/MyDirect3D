//
//	Transform.h
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<d3dx9.h>
#include<vector>

//===============================================
//	Transform : 3D専用　クラス
//===============================================
class Transform
{
public:
	static std::vector<Transform*> pIndex;	//Transform配列

public:
	static void ConvertReset();			//再変換を可能に

private:
	Transform* pParent;					//親
	std::vector<Transform*> pChild;		//子
	D3DXMATRIX MtxWorld;				//自身の変換行列

public :
	bool bConverted;					//変換したか

	//ワールド情報
	D3DXVECTOR3 Position;	//・World Position	(pParent->Position + this->position)
	D3DXVECTOR3 Scale;		//・World Scale		(pParent->Scale + this->scale)
	D3DXVECTOR3 Rotation;	//・World Rotation	(pParent->Rotation + this->rotation)
	
	//ローカル情報
	D3DXVECTOR3 position;	//・local Position 位置
	D3DXVECTOR3 scale;		//・local Scale サイズ
	D3DXVECTOR3 rotation;	//・local Rotation 回転

	//軸方向
	D3DXVECTOR3 up;			//・上
	D3DXVECTOR3 forward;	//・前
	D3DXVECTOR3 right;		//・右

public:
	//コンストラクタ
	Transform() :Transform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }){};
	Transform(D3DXVECTOR3 Position) :Transform(Position, { 1.0f,1.0f,1.0f }, {0.0f,0.0f,0.0f}) {};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale) :Transform(Position, Scale, { 0.0f,0.0f,0.0f }) {};
	Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation);

	~Transform();
	
public:
	D3DXMATRIX Convert();	//行列変換開始
	void Release_Parent();					//親を放す

public:
	//SET関数
	void Set_Parent(Transform* pParent);	//親を設定
	Transform* Set_UpdateTransform();		//情報を更新する		
public:
	//GET関数
	Transform* Get_Parent();				//親を取得
};

//===============================================
//	Transform2 : 2D専用　クラス
//===============================================
class Transform2
{
private:

public:
	D3DXVECTOR2 Position;	//位置
	D3DXVECTOR2 Scale;		//サイズ
	float Rotation;			//回転
	D3DCOLOR Color;			//色

	//コンストラクタ
	Transform2();
	Transform2(D3DXVECTOR2 Position,D3DXVECTOR2 Scale,float Rotation);
	Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation,D3DCOLOR Color);
	
};

#endif
