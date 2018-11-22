//
//	XModel.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	�ύX�� Changed By 
//		Name:Minoda Takamasa DATE:2018/10/23
//		Name:HIROMASA IKEDA	 DATE:2018/11/15
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include"common.h"
#include<d3dx9.h>
#include<string.h>
#include<Windows.h>

#include"XModel.h"
#include"System.h"

//Class
#include"CMesh.h"

//===============================================
//	�}�N����`		define
//===============================================
#define MESH_AMOUNT (1)
#define MESH_MAX (1)

#define MODELS_FILE ("Models/")

//===============================================
//	�O���[�o���ϐ�	global
//===============================================

MeshData g_Mesh[MeshIndexMax]; //���b�V���f�[�^���X�g

//===============================================
//	XModel ���O���
//===============================================
namespace XModel 
{
	//�f�[�^�ۑ�
	static Data Index[NAME_END];

	//---------------------------------
	//	���f���ǂݍ���
	//---------------------------------
	void Load(const int index)
	{
		HRESULT hr;
		char FilePath[100] = {"\0"};

		strcat(FilePath,MODELS_FILE);
		strcat(FilePath,path[index].FileName);
		strcat(FilePath,"/*.x");

		WIN32_FIND_DATA WindData = {};

		HANDLE hFind = FindFirstFile(FilePath,&WindData);

		if(hFind == INVALID_HANDLE_VALUE)
		{
			strcat(FilePath, "\n��������܂���B");
			MessageBox(*System_GethWnd(), FilePath, "�G���[", MB_OK);
			DestroyWindow(*System_GethWnd());
			return;
		}

		strcpy(FilePath,"\0");

		strcat(FilePath,MODELS_FILE);
		strcat(FilePath,path[index].FileName);
		strcat(FilePath,"/");
		strcat(FilePath,WindData.cFileName);

		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

		hr = D3DXLoadMeshFromX(
			FilePath,
			D3DXMESH_SYSTEMMEM,
			System_GetDevice(),
			NULL,
			&pD3DXMtrlBuffer,
			NULL,
			&Index[index].dwNumMaterials,
			&Index[index].pMesh
		);

		if (FAILED(hr))
		{
			char ErrorText[100] = { "\0" };
			strcat(ErrorText, FilePath);
			strcat(ErrorText, "\n���f���f�[�^���ǂݍ��߂܂���ł����B");

			MessageBox(*System_GethWnd(), ErrorText, "�G���[", MB_OK);
			DestroyWindow(*System_GethWnd());
			return;
		}

		strcpy(FilePath, "\0");	//������
		strcat(FilePath, MODELS_FILE);
		strcat(FilePath, path[index].FileName);
		strcat(FilePath, "/");

		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		Index[index].pMaterials = new D3DMATERIAL9[Index[index].dwNumMaterials];
		Index[index].pTextures = new LPDIRECT3DTEXTURE9[Index[index].dwNumMaterials];

		D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

		for (DWORD i = 0; i < Index[index].dwNumMaterials; i++)
		{
			Index[index].pMaterials[i] = d3dxMaterials[i].MatD3D;
			Index[index].pMaterials[i].Ambient = Index[index].pMaterials[i].Diffuse;
			Index[index].pTextures[i] = NULL;

			if (d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
			{
				//�e�N�X�`���̃p�X
				char TexturePath[200] = { "\0" };
				strcat(TexturePath, FilePath);
				strcat(TexturePath, d3dxMaterials[i].pTextureFilename);

				hr = D3DXCreateTextureFromFile(
					System_GetDevice(),
					TexturePath,
					&Index[index].pTextures[i]
				);

				if (FAILED(hr))
				{
					char ErrorText[200] = { "\0" };
					strcat(ErrorText, TexturePath);
					strcat(ErrorText, "\n�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B");

					MessageBox(NULL, ErrorText, "�G���[", MB_OK);
				}
			}
		}
		pD3DXMtrlBuffer->Release();
	}

	//---------------------------------
	//	�S�Ẵ��f���ǂݍ���
	//---------------------------------
	void Load()
	{
		for(int index = 0; index<NAME_END; index++)
		{
			Load(index);
		}
	}

	//---------------------------------
	//	�`��
	//---------------------------------
	void Render(const int index)
	{
		//�}�e���A���̐��������[�v������
		for (DWORD i = 0; i < Index[index].dwNumMaterials; i++)
		{
			//�}�e���A���ݒ�
			System_GetDevice()->SetMaterial(&Index[index].pMaterials[i]);
			//�e�N�X�`���ݒ�
			System_GetDevice()->SetTexture(0, Index[index].pTextures[i]);
			//�����_�����O
			Index[index].pMesh->DrawSubset(i);
		}
	}

	//---------------------------------
	//	�I������
	//---------------------------------
	void Finalize()
	{
		for (DWORD i = 0; i < NAME_END; i++)
		{
			delete Index[i].pTextures;
			delete Index[i].pMaterials;
			Index[i].pMesh->Release();
		}
	}

	//---------------------------------
	//	���f�� �f�[�^�擾
	//---------------------------------
	Data* Get(const Name name)
	{
		return &Index[name];
	}

}

//===============================================
//	�֐�			function
//===============================================

CXModelMesh* XModelData_Load(char ModelFile[10])
{
	CXModelMesh* pModel = new CXModelMesh();

	HRESULT hr;
	char FilePath[60] = {"\0"};

	strcat(FilePath,MODELS_FILE);
	strcat(FilePath,ModelFile);
	strcat(FilePath,"/*.x");

	WIN32_FIND_DATA WindData = {};
	
	HANDLE hFind = FindFirstFile(FilePath,&WindData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		strcat(FilePath, "\n��������܂���B");
		MessageBox(*System_GethWnd(), FilePath, "�G���[", MB_OK);
		DestroyWindow(*System_GethWnd());
		return NULL;
	}

	strcpy(FilePath, "\0");					//�����񏉊���
											//���f���̃p�X���쐬
	strcat(FilePath, MODELS_FILE);
	strcat(FilePath, ModelFile);
	strcat(FilePath, "/");
	strcat(FilePath, WindData.cFileName);

	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	hr = D3DXLoadMeshFromX(
		FilePath,
		D3DXMESH_SYSTEMMEM,
		System_GetDevice(),
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		&pModel->dwNumMaterials,
		&pModel->pMesh
	);

	if (FAILED(hr))
	{
		char ErrorText[100] = { "\0" };
		strcat(ErrorText, FilePath);
		strcat(ErrorText, "\n���f���f�[�^���ǂݍ��߂܂���ł����B");

		MessageBox(*System_GethWnd(), ErrorText, "�G���[", MB_OK);
		DestroyWindow(*System_GethWnd());
		return NULL;
	}

	strcpy(FilePath, "\0");	//������
	strcat(FilePath, MODELS_FILE);
	strcat(FilePath, ModelFile);
	strcat(FilePath, "/");

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pModel->pMeshMaterials = new D3DMATERIAL9[pModel->dwNumMaterials];
	pModel->pMeshTextures = new LPDIRECT3DTEXTURE9[pModel->dwNumMaterials];

	D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	for (DWORD i = 0; i < pModel->dwNumMaterials; i++)
	{
		pModel->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		pModel->pMeshMaterials[i].Ambient = pModel->pMeshMaterials[i].Diffuse;
		pModel->pMeshTextures[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			//�e�N�X�`���̃p�X
			char TexturePath[200] = { "\0" };
			strcat(TexturePath, FilePath);
			strcat(TexturePath, d3dxMaterials[i].pTextureFilename);

			hr = D3DXCreateTextureFromFile(
				System_GetDevice(),
				TexturePath,
				&pModel->pMeshTextures[i]
			);

			if (FAILED(hr))
			{
				char ErrorText[200] = { "\0" };
				strcat(ErrorText, TexturePath);
				strcat(ErrorText, "\n�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B");

				MessageBox(NULL, ErrorText, "�G���[", MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	return pModel;
}

//-------------------------------------
//	�V�����ǂݍ��� �����ɂ̓��f���������Ă�t�@�C�����w��B
//-------------------------------------
void XModel_Load(MeshData *pMesh, char ModelFile[30] , D3DXVECTOR3* pvecPosition)
{
	HRESULT hr;
	char FilePath[60] = {"\0"};				//�����t�@�C���p�X

	strcat(FilePath,MODELS_FILE);			//���f���ۑ��t�@�C��
	strcat(FilePath,ModelFile);
	strcat(FilePath, "/*.x");

	WIN32_FIND_DATA WindData = {};			//���������f�[�^

	HANDLE hFind = FindFirstFile(FilePath,&WindData);	//�f�[�^��������

	if( hFind == INVALID_HANDLE_VALUE)
	{
		strcat(FilePath,"\n��������܂���B");
		MessageBox(*System_GethWnd(),FilePath,"�G���[",MB_OK);
		DestroyWindow(*System_GethWnd());
		return;
	}

	strcpy(FilePath,"\0");					//�����񏉊���

	//���f���̃p�X���쐬
	strcat(FilePath, MODELS_FILE);			
	strcat(FilePath, ModelFile);
	strcat(FilePath, "/");
	strcat(FilePath, WindData.cFileName);

	//	X���f�� �ǂݍ���
	//--------------------------

	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	hr = D3DXLoadMeshFromX(
		FilePath,
		D3DXMESH_SYSTEMMEM,
		System_GetDevice(),
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		&pMesh->dwNumMaterials,
		&pMesh->pMesh
	);

	//--------------------------

	if(FAILED(hr))
	{
		char ErrorText[100] = {"\0"};
		strcat(ErrorText,FilePath);
		strcat(ErrorText,"\n���f���f�[�^���ǂݍ��߂܂���ł����B");

		MessageBox(*System_GethWnd(),ErrorText,"�G���[",MB_OK);
		DestroyWindow(*System_GethWnd());
		return;
	}

	//	���f���e�N�X�`���@�ǂݍ���
	//--------------------------

	strcpy(FilePath,"\0");	//������
	strcat(FilePath, MODELS_FILE);			
	strcat(FilePath, ModelFile);
	strcat(FilePath, "/");

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pMesh->pMeshMaterials = new D3DMATERIAL9[pMesh->dwNumMaterials];
	pMesh->pMeshTextures = new LPDIRECT3DTEXTURE9[pMesh->dwNumMaterials];

	D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	for (DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		pMesh->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		pMesh->pMeshMaterials[i].Ambient = pMesh->pMeshMaterials[i].Diffuse;
		pMesh->pMeshTextures[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			//�e�N�X�`���̃p�X
			char TexturePath[200] = { "\0" };
			strcat(TexturePath,FilePath);
			strcat(TexturePath, d3dxMaterials[i].pTextureFilename);

			hr = D3DXCreateTextureFromFile(
				System_GetDevice(),
				TexturePath,
				&pMesh->pMeshTextures[i]
			);

			if (FAILED(hr))
			{
				char ErrorText[200] = { "\0" };
				strcat(ErrorText,TexturePath);
				strcat(ErrorText,"\n�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B");

				MessageBox(NULL, ErrorText, "�G���[", MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	return;
}

//-------------------------------------
//	�`��
//-------------------------------------	
void XModel_Render(MeshData *pMesh)
{
	MeshData *pMeshData = pMesh;
	System_GetDevice()->SetTransform(D3DTS_WORLD, &pMeshData->matWorld);

	//�}�e���A���̐��������[�v������
	for (DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		//�}�e���A���ݒ�
		System_GetDevice()->SetMaterial(&pMesh->pMeshMaterials[i]);
		//�e�N�X�`���ݒ�
		System_GetDevice()->SetTexture(0, pMesh->pMeshTextures[i]);
		//�����_�����O
		pMesh->pMesh->DrawSubset(i);
	}
}

void XModel_Render(MeshData *pMesh, D3DXMATRIXA16 mtx)
{
	MeshData *pMeshData = pMesh;
	D3DXMATRIXA16 mtxWorld = pMeshData->matWorld * mtx;
	System_GetDevice()->SetTransform(D3DTS_WORLD, &mtx);

	//�}�e���A���̐��������[�v������
	for (DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		//�}�e���A���ݒ�
		System_GetDevice()->SetMaterial(&pMesh->pMeshMaterials[i]);
		//�e�N�X�`���ݒ�
		System_GetDevice()->SetTexture(0, pMesh->pMeshTextures[i]);
		//�����_�����O
		pMesh->pMesh->DrawSubset(i);
	}
}

//-------------------------------------
//	������
//-------------------------------------
void XModel_Initialize()
{
	
}

//-------------------------------------
//	�I��
//-------------------------------------
void XModel_Finalize() 
{
	for (DWORD i = 0; i < MESH_MAX; i++)
	{
		delete g_Mesh[i].pMeshTextures;
		delete g_Mesh[i].pMeshMaterials;
		g_Mesh[i].pMesh->Release();
	}
}

MeshData* GetMeshData(int MeshIndex)
{
	return &g_Mesh[MeshIndex];
}
