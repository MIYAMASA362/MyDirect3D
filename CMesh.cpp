//
//	CMesh.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/14
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include"System.h"

//class
#include"Cube.h"
#include"CMesh.h"
#include"XModel.h"

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================

//===============================================
//	CMesh ����
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
AMesh::AMesh()
{
	
}

//===============================================
//	CStandardMesh
//===============================================

//-------------------------------------
//	�R���X�g���N�^
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
//	�`��
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
//	CXModelMesh X���f���f�[�^
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
CXModelMesh::CXModelMesh()
{

}

//-------------------------------------
//	�`��
//-------------------------------------
void CXModelMesh::begin()
{
	//�}�e���A���̐��������[�v������
	for (DWORD i = 0; i < this->dwNumMaterials; i++)
	{
		//�}�e���A���ݒ�
		System_GetDevice()->SetMaterial(&this->pMeshMaterials[i]);
		//�e�N�X�`���ݒ�
		System_GetDevice()->SetTexture(0, this->pMeshTextures[i]);
		//�����_�����O
		this->pMesh->DrawSubset(i);
	}
}

//===============================================
//	���f����
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
CXModelName::CXModelName(XModel::Name name)
{
	this->Model = name;
}

//-------------------------------------
//	�`��
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



