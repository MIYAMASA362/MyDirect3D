//
//	MeshField_Cylinder.cpp
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#include<d3dx9.h>
#define _USE_MATH_DEFINES
#include<math.h>

#include"MeshField_Cylinder.h"
#include"Texture.h"

#include"System.h"

//Class

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	グローバル変数	global
//===============================================
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

static MeshFieldVertex* g_pVertex = NULL;
static WORD* g_pIndex = NULL;

static D3DMATERIAL9 g_Material;
static int VertexNum = (MESH_CYLINDER_GRID_WIDTH + 1) * (MESH_CYLINDER_GRID_HEIGHT + 1) + ((MESH_CYLINDER_GRID_HEIGHT - 1) * 2);

static D3DXVECTOR3 g_Center;

//===============================================
//	関数			function
//===============================================


//-------------------------------------
//	初期化
//-------------------------------------
void MeshCylinder_Initialize()
{
	
	g_Material.Diffuse = g_Material.Ambient = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	System_GetDevice()->CreateVertexBuffer(
		sizeof(MeshFieldVertex) * (MESH_CYLINDER_GRID_WIDTH + 1) * (MESH_CYLINDER_GRID_HEIGHT + 1),
		D3DUSAGE_WRITEONLY,
		FVF_MESHFIELD,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);

	System_GetDevice()->CreateIndexBuffer(
		sizeof(DWORD) * VertexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);

	//頂点データ
	g_pVertexBuffer->Lock(0,0,(void**)&g_pVertex,0);

	int nCount = 0;	//頂点カウント	

	float th = (float)(1.0f / (MESH_CYLINDER_GRID_HEIGHT));	//テクスチャ縦
	float tw = (float)(1.0f / (MESH_CYLINDER_GRID_WIDTH)*2);

	//Y軸
	for(int i = 0; i < (MESH_CYLINDER_GRID_HEIGHT+ 1); i++ )
	{
		float y = (float)MESH_HEIGHT * i;	//Y軸

		//一回転
		for(int j = 0; j < (MESH_CYLINDER_GRID_WIDTH + 1); j++)
		{
			float x = (float)MESH_CYLINDER_RADIUS * sinf((float)(j * MESH_ANGLE));	//X軸
			float z = (float)MESH_CYLINDER_RADIUS * cosf((float)(j * MESH_ANGLE));	//Z軸

			g_pVertex[nCount].Position	= D3DXVECTOR3(x,y,z);
			g_pVertex[nCount].Normal	= D3DXVECTOR3(0,-1,0);
			g_pVertex[nCount].TexCoord	= D3DXVECTOR2(tw * j, 1 - (th * i));
			nCount++;
		}
	}

	g_pVertexBuffer->Unlock();

	g_pIndexBuffer->Lock(0,0,(void**)&g_pIndex,0);

	nCount = 0;

	//Y軸
	for(int i = 0; i< (MESH_CYLINDER_GRID_HEIGHT + 1); i++)
	{
		int j = 0;

		//縮退ポリゴン
		if (i > 0)
		{
			g_pIndex[nCount] = g_pIndex[nCount -1];
			g_pIndex[nCount + 1] = ((MESH_CYLINDER_GRID_WIDTH + 1)* i) + j;
			nCount += 2;
		}
		
		//回転
		for(; j < (MESH_CYLINDER_GRID_WIDTH + 1); j++)
		{
			g_pIndex[nCount] = ((MESH_CYLINDER_GRID_WIDTH + 1) * i) + j; //0
			g_pIndex[nCount + 1] = ((MESH_CYLINDER_GRID_WIDTH + 1) * (i+1) + j); //1
			nCount += 2;
		}
	}

	g_pIndexBuffer->Unlock();

}

void MeshCylinder_Render(const D3DXVECTOR3 Center,TEXTURE_NAME Texture)
{
	g_Center = Center;
	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	D3DXMATRIX mtxWorld;
	D3DXMatrixTranslation(&mtxWorld, Center.x, 0, Center.z);
	Device->SetTransform(D3DTS_WORLD, &mtxWorld);
	Device->SetMaterial(&g_Material);
	Device->SetStreamSource(0, g_pVertexBuffer,0,sizeof(MeshFieldVertex));
	Device->SetIndices(g_pIndexBuffer);
	Device->SetFVF(FVF_MESHFIELD);
	Device->SetTexture(0,Texture_GetTexture(Texture));
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0, VertexNum,0,(MESH_CYLINDER_GRID_HEIGHT * MESH_CYLINDER_GRID_WIDTH + ((MESH_CYLINDER_GRID_HEIGHT -1) * 2)) * 2);
}

D3DXVECTOR3 MeshCylinder_GetCenter()
{
	return g_Center;
}

void MeshCylinder_Finalize()
{
	if(g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}

	if(g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}