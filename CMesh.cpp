//
//	CMesh.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/14
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#include"System.h"

//class
#include"Cube.h"
#include"CMesh.h"
#include"XModel.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================

//===============================================
//	CMesh 抽象
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
AMesh::AMesh()
{
	
}

//===============================================
//	CStandardMesh
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CStandardMesh::CStandardMesh():AMesh()
{
	this->texture = Texture();
	this->FVF = FVF_CUBE_VERTEX3D;
	this->PrimitiveType = CUBE_PRIMITIVE_TYPE;
	this->Model = GetModel_Cube();
	this->DataSize = sizeof(CubeVertex3D);
	this->PrimitiveCount = CUBE_PRIMITIVE_NUM;
}

//-------------------------------------
//	描画
//-------------------------------------
void CStandardMesh::begin()
{
	System_GetDevice()->SetFVF(this->FVF);

	if (this->texture.Texture_index == TEXTURE_NONE)
	{
		System_GetDevice()->SetTexture(0, NULL);
	}
	else
	{
		System_GetDevice()->SetTexture(0, Texture_GetTexture(this->texture.Texture_index));
	}

	System_GetDevice()->DrawPrimitiveUP(this->PrimitiveType, this->PrimitiveCount, this->Model, this->DataSize);
}

//===============================================
//	CXModelMesh Xモデルデータ
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CXModelMesh::CXModelMesh()
{

}

//-------------------------------------
//	描画
//-------------------------------------
void CXModelMesh::begin()
{
	//マテリアルの数だけループさせる
	for (DWORD i = 0; i < this->dwNumMaterials; i++)
	{
		//マテリアル設定
		System_GetDevice()->SetMaterial(&this->pMeshMaterials[i]);
		//テクスチャ設定
		System_GetDevice()->SetTexture(0, this->pMeshTextures[i]);
		//レンダリング
		this->pMesh->DrawSubset(i);
	}
}

//===============================================
//	モデル名
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CXModelName::CXModelName(XModel::Name name)
{
	this->Model = name;
}

//-------------------------------------
//	描画
//-------------------------------------
void CXModelName::begin()
{
	XModel::Data* pMesh = XModel::Get(Model);

	for(DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		System_GetDevice()->SetMaterial(&pMesh->pMaterials[i]);
		System_GetDevice()->SetTexture(0,pMesh->pTextures[i]);
		pMesh->pMesh->DrawSubset(i);
	}
}



