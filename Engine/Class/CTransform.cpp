//
//	Transform.cpp
//		Author:HIROMASA IKEDA	DATA:2018/11/22
//===============================================
#include<d3dx9.h>
#include"CTransform.h"

//===============================================
//	グローバル変数
//===============================================
std::vector<Transform*> Transform::pIndex;

//===============================================
//	ATransform
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
ATransform::ATransform()
{

}

//-------------------------------------
//	デストラクタ
//-------------------------------------
ATransform::~ATransform()
{
	
}

//===============================================
//	BasicTransform
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
BasicTransform::BasicTransform()
{

}

//-------------------------------------
//	デストラクタ
//-------------------------------------
BasicTransform::~BasicTransform()
{

}

//===============================================
//	Transform
//===============================================

//-------------------------------------
//	再変換を可能
//-------------------------------------
void Transform::ConvertReset()
{
	for(int i = 0; i < pIndex.size();i++)
	{
		pIndex.at(i)->bConverted = false;	//Windowでエラーが起きる原因っぽい
	}
}

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Transform::Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation)
{
	this->bConverted = false;
	this->pParent = NULL;

	//ワールド情報
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;

	//ローカル情報
	this->position = Position;
	this->scale = Scale;
	this->rotation = Rotation;

	this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3Normalize(&this->forward, &this->forward);
	D3DXVec3Cross(&this->right, &this->forward, &this->up);
	D3DXVec3Normalize(&this->right, &this->right);

	pIndex.push_back(this);
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
Transform::~Transform()
{
	this->pParent = NULL;

	//子を持っているなら
	if (this->pChild.size() > 0)
	{
		for (int i = 0; i < this->pChild.size(); i--)
		{
			//子に親の死亡を伝える
			this->pChild.at(i)->Release_Parent();
		}
	}

	this->pChild.clear();
}

//-------------------------------------
//	親を設定
//-------------------------------------
void Transform::Set_Parent(Transform* pParent)
{
	this->pParent = pParent;
	pParent->pChild.push_back(this);	//親に子を覚えさせる

	this->Position = pParent->Position + this->position;
	this->Scale = pParent->Scale + this->scale;
	this->Rotation = pParent->Rotation + this->rotation;

}

//-------------------------------------
//	情報を更新
//-------------------------------------
Transform* Transform::Set_UpdateTransform()
{
	if (this->pParent != NULL)
	{
		this->Position = pParent->Position + this->position;
		this->Scale = pParent->Scale + this->scale;
		this->Rotation = pParent->Rotation + this->rotation;
	}
	else
	{
		this->Position = this->position;
		this->Rotation = this->rotation;
		this->Scale = this->scale;
	}

	return this;
}

//-------------------------------------
//	親を取得
//-------------------------------------	
Transform* Transform::Get_Parent()
{
	return this->pParent;
}

//-------------------------------------
//	行列変換
//-------------------------------------
D3DXMATRIX Transform::Convert()
{
	this->bConverted = false;
	this->Set_UpdateTransform();
	if (this->bConverted) return this->MtxWorld;	//一度変換されている

	//各行列
	D3DXMATRIX MtxTransform;	//位置
	D3DXMATRIX MtxScale;		//大きさ
	D3DXMATRIX MtxRotation;		//回転

	//行列変換
	D3DXMatrixTranslation(&MtxTransform, this->position.x, this->position.y, this->position.z);
	D3DXMatrixScaling(&MtxScale, this->scale.x, this->scale.y, this->scale.z);
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->rotation.y, this->rotation.x, this->rotation.z);

	//上情報
	this->up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXVec3TransformNormal(&this->up,&this->up,&MtxRotation);
	D3DXVec3Normalize(&this->up, &this->up);

	//前情報
	this->forward = D3DXVECTOR3(0.0f,0.0f,1.0f);
	D3DXVec3TransformNormal(&this->forward,&this->forward,&MtxRotation);
	D3DXVec3Normalize(&this->forward, &this->forward);

	//右情報
	D3DXVec3Cross(&this->right, &this->up, &this->forward);

	//ワールド行列の作成
	D3DXMatrixIdentity(&this->MtxWorld);
	this->MtxWorld = MtxScale * MtxRotation * MtxTransform;

	//親が居る
	if (this->pParent != NULL)
	{
		//親の行列見てくる
		this->MtxWorld *= this->pParent->Convert();
	}

	//変換終了	
	this->bConverted = true;

	return this->MtxWorld;
}

//-------------------------------------
//	親を放す
//-------------------------------------
void Transform::Release_Parent()
{
	this->pParent = NULL;
}

//===============================================
//	Transform2
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Transform2::Transform2()
{
	Position = { 0.0f,0.0f };
	Scale = { 1.0f,1.0f };
	Rotation = 0;
	Color = Color;
}

Transform2::Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation)
{
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;
	Color = D3DCOLOR_RGBA(255, 255, 255, 255);
}

Transform2::Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation, D3DCOLOR Color)
{
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;
	this->Color = Color;
}
