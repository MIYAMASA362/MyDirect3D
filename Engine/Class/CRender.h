//
//	CRender.h
//		Author:HIROMASA IKEDA	DATE:2018/09/29
//===============================================
#pragma once
#ifndef CRENDER_H
#define CRENDER_H

#include<d3dx9.h>
#include<vector>

//Class
#include"Component.h"
#include"CTransform.h"
#include"CTexture.h"
#include"CAnimation.h"

#include"XModel.h"
#include"CMesh.h"	

//===============================================
//	列挙
//===============================================

//===============================================
//	構造体
//===============================================

//===============================================
//	クラス
//===============================================

//-------------------------------------
//	Render3D
//-------------------------------------
class Render3D
{
private:
	AMesh* pModel;		//モデルデータ

public:
	bool bRender;		//描画するか

public:
	Render3D();
	~Render3D();

public:
	void SetMesh(AMesh* pModel);
	void Begin(Transform* pTransform);
};

//-------------------------------------
//	Render2D
//-------------------------------------
class Render2D
{
public:

	enum RENDER2D_TYPE
	{
		R2D_PORIGON,
		R2D_RORIGON_ROTATE,
		R2D_TEXTURE_SIZE,
		R2D_TEXTURE_FILL,
		R2D_TEXTURE_CLIP,
		R2D_SPRITE,
		R2D_SPRITE_ROTATE
	};

	//アニメーション
	enum RENDER2DANIMA_TYPE
	{
		R2DA_NOLOOP,
		R2DA_LOOP,
		R2DA_LOOP_ROTATE
	};

private:

public:
	Transform2* pTransform;
	Texture*	pTexture;
	Animation*	pAnimation;

public:
	//コンストラクタ
	Render2D();
	Render2D(Transform2* pTransform, Texture* pTexture);
	Render2D(Transform2* pTransform, Texture* pTexture, Animation* pAnimation);

public:
	bool Begin(RENDER2D_TYPE R2D_TYPE);
	bool Begin(RENDER2DANIMA_TYPE R2DA_TYPE);
};

#endif // !CRENDER_H
