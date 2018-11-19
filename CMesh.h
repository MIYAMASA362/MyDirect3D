//
//	CMesh.h
//		Author:HIROMASA IEKDA	DATE:2018/11/14
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CMESH_H
#define CMESH_H

//================================================
//	インクルード	include
//================================================
#include<d3dx9.h>
#include"common.h"

#include"CTexture.h"
#include"XModel.h"

using namespace XModel;

//================================================
//	マクロ定義	define
//================================================


//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================


//===============================================
//	クラス
//===============================================

//===============================================
//	AMesh 抽象
//===============================================
class AMesh
{
private:

public:
	AMesh();

public:
	virtual void begin() = 0;	//描画

};

//===============================================
//	CStandardMesh
//===============================================
class CStandardMesh :public AMesh
{
private:

public:
	Texture texture;
	DWORD FVF;
	D3DPRIMITIVETYPE PrimitiveType;
	void* Model;
	UINT DataSize;
	UINT PrimitiveCount;

public:
	CStandardMesh();

public:
	void begin() override;
};

//===============================================
//	CXModelMesh Xモデルデータ
//===============================================
class CXModelMesh :public AMesh
{
private:

public:
	LPD3DXMESH pMesh;
	D3DMATERIAL9* pMeshMaterials;
	LPDIRECT3DTEXTURE9* pMeshTextures;
	DWORD dwNumMaterials;

public:
	CXModelMesh();

public:
	void begin() override;
};

//===============================================
//	CXModelName Xモデル名
//===============================================
class CXModelName :public AMesh
{
public:
	//モデル名を登録
	Name Model;
public:
	CXModelName(Name name);
public:
	void begin() override;
};

#endif