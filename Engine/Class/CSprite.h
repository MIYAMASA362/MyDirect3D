//
//	CSprite.h
//		Author:HIROMASA IEKDA	DATE:2018/10/01
//===============================================
#pragma once
#include<d3dx9.h>
#include"CTransform.h"
#include"CAnimation.h"
#include"CRender.h"

//===============================================
//	Sprite クラス
//===============================================
class Sprite
{
private:

public:
	Render2D render;
	Transform2 transform;	//位置
	Texture texture;		//テクスチャ
	Animation animation;	//アニメーションステータス

	//コンストラクタ
	Sprite();
	Sprite(Transform2* pTransform2,Texture* pTexture);
	Sprite(Transform2* pTransform2,Texture* pTexture,Animation* pAnimation);

};


