//
//	CSprite.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/01
//===============================================
#include<d3dx9.h>
#include"CSprite.h"
#include"Sprite.h"

//===============================================
//	Spriteクラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Sprite::Sprite()
{

}

//-------------------------------------
//	コンストラクタ　ポインタ型
//-------------------------------------
Sprite::Sprite(Transform2* pTransform2, Texture* pTexture) :render(&this->transform,&this->texture)
{
	this->transform = *pTransform2;
	this->texture = *pTexture;
	this->animation = {};
}

Sprite::Sprite(Transform2* pTransform2, Texture* pTexture, Animation* pAnimation):render(&this->transform,&this->texture,&this->animation)
{
	this->transform		= *pTransform2;
	this->texture		= *pTexture;
	this->animation		= *pAnimation;
}