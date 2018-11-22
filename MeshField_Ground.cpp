//
//	MeshField_Ground.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/25
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//UV���W�ɂ��ẮA�����ł���p�� UV�A�h���b�V���O���[�h
//1���� N = x + w * z
// x�͉��̌��ݒn�@w �͉��̍ő�l�@z �͌��݂̐[�x
// D3DRS_FILLEMODE D3DFILL_WIREFLAME

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include<d3dx9.h>

#include"MeshField_Ground.h"
#include"Texture.h"

#include"System.h"

//Class

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================
static LPDIRECT3DVERTEXBUFFER9	g_pMeshField_Ground_VertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9	g_pMeshField_Ground_IndexBuffer = NULL;

static MeshFieldVertex3D* g_pMeshField_Ground_Vertex = NULL;
static WORD* g_pMeshField_Ground_Index = NULL;

static int ReturnNum = MESHFIELD_GRIDNUM_DEPTH - 1;	//�܂�Ԃ���
static int VertexNum = ((MESHFIELD_GRIDNUM_WIDTH + 1) * 2) * MESHFIELD_GRIDNUM_DEPTH + (2 * ReturnNum);
static int PrimitiveNum = VertexNum - 2;
static D3DMATERIAL9 g_Material;

//===============================================
//	�֐�			function
//===============================================

//-------------------------------------
//	������
//-------------------------------------
void MeshField_Ground_Initialize() 
{
	g_Material.Diffuse = g_Material.Ambient = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	System_GetDevice()->CreateVertexBuffer(
		sizeof(MeshFieldVertex3D) * (MESHFIELD_GRIDNUM_WIDTH + 1) * (MESHFIELD_GRIDNUM_DEPTH + 1),
		D3DUSAGE_WRITEONLY,
		FVF_MESHFIELD_VERTEX3D,
		D3DPOOL_MANAGED,
		&g_pMeshField_Ground_VertexBuffer,
		NULL
	);

	System_GetDevice()->CreateIndexBuffer(
		sizeof(DWORD) * VertexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pMeshField_Ground_IndexBuffer,
		NULL
	);

	int nCount = 0;

	//���_�f�[�^
	g_pMeshField_Ground_VertexBuffer->Lock(0, 0, (void**)&g_pMeshField_Ground_Vertex, 0);

	//��
	const float fWidth = MESHFIELD_SIZE_WIDTH / MESHFIELD_GRIDNUM_WIDTH;
	const float fDepth = MESHFIELD_SIZE_DEPTH / MESHFIELD_GRIDNUM_DEPTH;

	//�����ʒu
	const float Initx = -MESHFIELD_SIZE_WIDTH * 0.5f;
	const float Initz = MESHFIELD_SIZE_DEPTH * 0.5f;

	float x = Initx;
	float z = Initz;

	//Z���J�E���g
	for (int i = 0; i< (MESHFIELD_GRIDNUM_DEPTH + 1); i++)
	{
		//X���J�E���g
		for (int j = 0; j < (MESHFIELD_GRIDNUM_WIDTH + 1); j++)
		{
			g_pMeshField_Ground_Vertex[nCount + j].Position = D3DXVECTOR3(x, 0, z);		//���W
			g_pMeshField_Ground_Vertex[nCount + j].Normal = D3DXVECTOR3(0, -1, 0);			//�@��
			g_pMeshField_Ground_Vertex[nCount + j].Color = D3DCOLOR_RGBA(200, 200, 200, 255);	//�F
			g_pMeshField_Ground_Vertex[nCount + j].TexCoord = D3DXVECTOR2((float)j, (float)i);				//UV���W
			x += fWidth;
		}

		nCount += (MESHFIELD_GRIDNUM_WIDTH + 1);
		x = Initx;		//�����ʒu�ɖ߂�
		z -= fDepth;	//Z�����ړ�
	}

	g_pMeshField_Ground_VertexBuffer->Unlock();

	nCount = 0;

	//�C���f�b�N�X
	g_pMeshField_Ground_IndexBuffer->Lock(0, 0, (void**)&g_pMeshField_Ground_Index, 0);

	//Z��
	for (int j = 0; j < MESHFIELD_GRIDNUM_DEPTH; j++)
	{
		int i = 0;

		//1��ڂ͓����Ȃ��B
		if (j>0)
		{
			//�k�ރ|���S��
			g_pMeshField_Ground_Index[nCount] = g_pMeshField_Ground_Index[nCount - 1];
			g_pMeshField_Ground_Index[nCount + 1] = ((MESHFIELD_GRIDNUM_WIDTH + 1) * (j + 1)) + i;
			nCount += 2;
		}

		//X��
		for (i = 0; i < (MESHFIELD_GRIDNUM_WIDTH + 1); i++)
		{
			g_pMeshField_Ground_Index[nCount] = ((MESHFIELD_GRIDNUM_WIDTH + 1) * (j + 1)) + i;	//0
			g_pMeshField_Ground_Index[nCount + 1] = ((MESHFIELD_GRIDNUM_WIDTH + 1) * j) + i;	//1
			nCount += 2;
		}
	}

	g_pMeshField_Ground_IndexBuffer->Unlock();

}

//-------------------------------------
//	�`��
//-------------------------------------
void MeshField_Ground_Render(const D3DXVECTOR3 Center,TEXTURE_NAME Texture)
{
	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	D3DXMATRIX mtxWorld;
	D3DXMatrixTranslation(&mtxWorld,Center.x,0,Center.z);
	Device->SetTransform(D3DTS_WORLD,&mtxWorld);
	Device->SetMaterial(&g_Material);
	Device->SetStreamSource(0,g_pMeshField_Ground_VertexBuffer,0,sizeof(MeshFieldVertex3D));
	Device->SetIndices(g_pMeshField_Ground_IndexBuffer);
	Device->SetFVF(FVF_MESHFIELD_VERTEX3D);
	Device->SetTexture(0,Texture_GetTexture(Texture));
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,VertexNum,0,PrimitiveNum);
}

//-------------------------------------
//	�I��
//-------------------------------------
void MeshField_Ground_Finalize() 
{
	if(g_pMeshField_Ground_IndexBuffer)
	{
		g_pMeshField_Ground_IndexBuffer->Release();
		g_pMeshField_Ground_IndexBuffer = NULL;
	}

	if(g_pMeshField_Ground_VertexBuffer)
	{
		g_pMeshField_Ground_VertexBuffer->Release();
		g_pMeshField_Ground_VertexBuffer = NULL;
	}
}
