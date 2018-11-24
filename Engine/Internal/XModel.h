//
//	XModel.h
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	�ύX�� Changed By
//		Name:Minoda Takamasa	DATE:2018/10/23
//
//-----------------------------------------------

#pragma once
#ifndef IKEDA_TEMPSOURCE_H
#define IKEDA_TEMPSOURCE_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include"CTexture.h"

//================================================
//	�}�N����`	define
//================================================
#define MODEL_FILENAME_MAX (64)

//================================================
//	�񋓌^		enum
//================================================
enum MeshIndex
{
	BulletIndex=0,
	ScrewIndex,
	MeshIndexMax
};

//================================================
//	�\����		struct/typedef
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
//	XModel ���O���
//===============================================
namespace XModel
{
	//���f���̃f�[�^�^
	struct Data
	{
		LPD3DXMESH pMesh;
		D3DMATERIAL9* pMaterials;
		LPDIRECT3DTEXTURE9* pTextures;
		DWORD dwNumMaterials;
	};

	//���f����
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

	//�A�N�Z�X
	struct Path
	{
		Name name;
		char FileName[30];
	};

	//�e���f����Path��ݒ�
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
	//	�֐�
	//------------------------------------
	void Load(const int index);
	void Load();
	void Render(const int index);
	void Finalize();
	Data* Get(const Name name);
}

//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	XModel
//================================================


//================================================
//	�֐�		function
//================================================
void XModel_Initialize();	//������
void XModel_Finalize();		//�I��

//void XModel_Load(MeshData *pMesh, char ModelFile[10], D3DXVECTOR3* pvecPosition);		//���f���ǂݍ���
void XModel_Render(MeshData *pMesh);	//�`��
void XModel_Render(MeshData *pMesh, D3DXMATRIXA16 mtx);
MeshData* GetMeshData(int MeshIndex);  //���b�V���f�[�^�̎擾


#endif