//
//	XModel.h
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	変更者 Changed By
//		Name:Minoda Takamasa	DATE:2018/10/23
//
//-----------------------------------------------

#pragma once
#ifndef IKEDA_TEMPSOURCE_H
#define IKEDA_TEMPSOURCE_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include"CTexture.h"

//================================================
//	マクロ定義	define
//================================================
#define MODEL_FILENAME_MAX (64)

//================================================
//	列挙型		enum
//================================================
enum MeshIndex
{
	BulletIndex=0,
	ScrewIndex,
	MeshIndexMax
};

//================================================
//	構造体		struct/typedef
//================================================
typedef struct MeshTag
{
	LPD3DXMESH pMesh;
	D3DMATERIAL9* pMeshMaterials;
	LPDIRECT3DTEXTURE9* pMeshTextures;
	DWORD dwNumMaterials;

	D3DXVECTOR3 vecPosition;
	D3DXMATRIXA16 matWorld;

}MeshData;


//===============================================
//	XModel 名前空間
//===============================================
namespace XModel
{
	//モデルのデータ型
	struct Data
	{
		LPD3DXMESH pMesh;
		D3DMATERIAL9* pMaterials;
		LPDIRECT3DTEXTURE9* pTextures;
		DWORD dwNumMaterials;
	};

	//モデル名
	const enum Name
	{
		AIRPLANE_BODY,
		AIRPLANE_PROPELLER,
		AIRPLANE_WingBD,
		AIRPLANE_WingBU,
		AIRPLANE_WingLD,
		AIRPLANE_WingLU,
		AIRPLANE_WingRD,
		AIRPLANE_WingRU,
		AIRPLANE_MODEL,
		TREE,
		NAME_END,
		MODEL_NONE
	};

	//アクセス
	struct Path
	{
		Name name;
		char FileName[30];
	};

	//各モデルのPathを設定
	static Path path[] = 
	{
		{AIRPLANE_BODY,"Airplane_Body"},
		{AIRPLANE_PROPELLER,"Airplane_Propeller"},
		{AIRPLANE_WingBD,"Airplane_WingBD"},
		{AIRPLANE_WingBU,"Airplane_WingBU"},
		{AIRPLANE_WingLD,"Airplane_WingLD"},
		{AIRPLANE_WingLU,"Airplane_WingLU"},
		{AIRPLANE_WingRD,"Airplane_WingRD"},
		{AIRPLANE_WingRU,"Airplane_WingRU"},
		{AIRPLANE_MODEL,"Airplane"},
		{TREE,"Tree"}
	};

	//------------------------------------
	//	関数
	//------------------------------------
	void Load(const int index);
	void Load();
	void Render(const int index);
	void Finalize();
	Data* Get(const Name name);
}

//================================================
//	グローバル変数　global
//================================================


//================================================
//	XModel
//================================================


//================================================
//	関数		function
//================================================
void XModel_Initialize();	//初期化
void XModel_Finalize();		//終了

//void XModel_Load(MeshData *pMesh, char ModelFile[10], D3DXVECTOR3* pvecPosition);		//モデル読み込み
void XModel_Render(MeshData *pMesh);	//描画
void XModel_Render(MeshData *pMesh, D3DXMATRIXA16 mtx);
MeshData* GetMeshData(int MeshIndex);  //メッシュデータの取得


#endif