//
//	CMesh.h
//		Author:HIROMASA IEKDA	DATE:2018/11/14
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CMESH_H
#define CMESH_H

//================================================
//	�C���N���[�h	include
//================================================
#include<d3dx9.h>
#include"common.h"

#include"CTexture.h"
#include"XModel.h"

using namespace XModel;

//================================================
//	�}�N����`	define
//================================================


//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//===============================================
//	�N���X
//===============================================

//===============================================
//	AMesh ����
//===============================================
class AMesh
{
private:

public:
	AMesh();

public:
	virtual void begin() = 0;	//�`��

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
//	CXModelMesh X���f���f�[�^
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
//	CXModelName X���f����
//===============================================
class CXModelName :public AMesh
{
public:
	//���f������o�^
	Name Model;
public:
	CXModelName(Name name);
public:
	void begin() override;
};

#endif