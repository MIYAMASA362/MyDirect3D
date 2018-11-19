//
//	Sprite.h
//		Author:HIROMASA IEDA	Date:2018/09/13
//===============================================
#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include<d3dx9.h>
#include"CTransform.h"
#include"CTexture.h"
#include"Texture.h"

//===============================================
//	構造体
//===============================================

//-------------------------------------
//	Vertex2D
//-------------------------------------
typedef struct Vertex2D
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
}Vertex2D;

//-------------------------------------
//	TexVertex2D
//-------------------------------------
typedef struct TexVertex2D
{
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 TexCoord;
}TexVertex2D;

//===============================================
//	関数
//===============================================

void Sprite_SetDevice(LPDIRECT3DDEVICE9 pD3DDevice);							//デバイス設定
void Render2D_Porigon(const Transform2* pTransform2);							//ポリゴン描画
void Render2D_Porigon_Circle(const Transform2* pTransform2,float radius);		//円ポリゴン
void Render2D_Line(D3DXVECTOR2 Vector1, D3DXVECTOR2 Vector2);					//線(太さとか設定できる線)
void Render2D_Porigon_Rotate(const Transform2* pTransform2);					//ポリゴン回転
void Render2D_Texture_Size(const Transform2* pTransform2, Texture* pTexture);	//画像サイズ描画
void Render2D_Texture_Fill(Transform2* pTransform2, Texture* pTexture);			//ポリゴンサイズに描画
void Render2D_Texture_Clip(Transform2* pTransform2, Texture* pTexture);			//テクスチャ切り抜きサイズ描画
void Render2D_Sprite(Transform2* pTransform2, Texture* pTexture);				//スプライト描画
void Render2D_Sprite_Rotate(Transform2* pTransform2, Texture* pTexture);		//回す

#endif

