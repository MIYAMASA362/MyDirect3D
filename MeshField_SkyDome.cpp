//
//	MeshField_SkyDome.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/26
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
#include"MeshField_SkyDome.h"

#include"System.h"
#include"Texture.h"

//Class

//===============================================
//	マクロ定義		define
//===============================================
#define MESH_SKYDORM_RADIUS (50)			//半径
#define MESH_SKYDORM_GRID_HEIGHT (50)	//縦を何グリッドにするか
#define MESH_SKYDORM_GRID_WIDTH (50)		//横を何グリッドか

#define FVF_SKYDORM_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

#define MESH_ANGLE_WIDTH	( (2*M_PI) / MESH_SKYDORM_GRID_WIDTH )
#define MESH_ANGLE_HEIGHT	( (M_PI_2) / MESH_SKYDORM_GRID_HEIGHT)
//===============================================
//	構造体
//===============================================
struct SkyDormVertex3D
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR2 TexCoord;
};

//===============================================
//	グローバル変数	global
//===============================================
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

static SkyDormVertex3D* g_pVertex = NULL;
static WORD* g_pIndex = NULL;

static D3DMATERIAL9 g_Material;
static int VertexNum = (MESH_SKYDORM_GRID_WIDTH + 1) * (MESH_SKYDORM_GRID_HEIGHT + 1) + ((MESH_SKYDORM_GRID_WIDTH -1)* 2);
//===============================================
//	関数			function
//===============================================


//-------------------------------------
//	初期化
//-------------------------------------
void MeshSkyDome_Initialize()
{
	g_Material.Diffuse = g_Material.Ambient = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	System_GetDevice()->CreateVertexBuffer(
		sizeof(SkyDormVertex3D) * (MESH_SKYDORM_GRID_WIDTH + 1) * (MESH_SKYDORM_GRID_HEIGHT + 1),
		D3DUSAGE_WRITEONLY,
		FVF_SKYDORM_VERTEX3D,
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

	g_pVertexBuffer->Lock(0,0,(void**)&g_pVertex,0);

	int nCount = 0; //頂点カウント

	//テクスチャ座標
	float th = (float)(1.0f / MESH_SKYDORM_GRID_HEIGHT);
	float tw = (float)(1.0f / MESH_SKYDORM_GRID_WIDTH);

	//Y軸
	for(int i = 0; i < (MESH_SKYDORM_GRID_HEIGHT + 1); i++)
	{
		float y = (float)(MESH_SKYDORM_RADIUS * sinf((float)MESH_ANGLE_HEIGHT * i));
		float radius = (float)(MESH_SKYDORM_RADIUS * cosf(MESH_ANGLE_HEIGHT * i));

		//一回転
		for(int j = 0;j< (MESH_SKYDORM_GRID_WIDTH + 1); j++)
		{
			float x = radius * sinf((float)(MESH_ANGLE_WIDTH * j));
			float z = radius * cosf((float)(MESH_ANGLE_WIDTH * j));

			g_pVertex[nCount].Position	= D3DXVECTOR3(x,y,z);
			g_pVertex[nCount].Normal	= D3DXVECTOR3(0,-1,0);
			g_pVertex[nCount].TexCoord	= D3DXVECTOR2(tw * j,1 -(th * i));
		
			nCount++;
		}
	}

	g_pVertexBuffer->Unlock();
	 
	nCount = 0;

	g_pIndexBuffer->Lock(0,0,(void**)&g_pIndex,0);

	//Y軸
	for(int i = 0; i < (MESH_SKYDORM_GRID_HEIGHT + 1); i++)
	{
		int j = 0;

		//縮退ポリゴン
		if(i > 0)
		{
			g_pIndex[nCount] = g_pIndex[nCount - 1];
			g_pIndex[nCount + 1] = ((MESH_SKYDORM_GRID_WIDTH + 1) * i) + j;
			nCount += 2;
		}

		//一回転
		for(; j < (MESH_SKYDORM_GRID_WIDTH + 1); j++)
		{
			g_pIndex[nCount] = ((MESH_SKYDORM_GRID_WIDTH + 1) * i) + j;
			g_pIndex[nCount + 1] = ((MESH_SKYDORM_GRID_WIDTH + 1) * (i + 1) + j);
			nCount += 2;
		}
	}

	g_pIndexBuffer->Unlock();
}

void MeshSkyDome_Render(const D3DXVECTOR3 Center,TEXTURE_NAME Texture)
{
	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	D3DXMATRIX mtxWorld;
	D3DXMatrixTranslation(&mtxWorld, Center.x, 0, Center.z);
	Device->SetTransform(D3DTS_WORLD, &mtxWorld);
	Device->SetMaterial(&g_Material);
	Device->SetStreamSource(0, g_pVertexBuffer,0,sizeof(SkyDormVertex3D));
	Device->SetIndices(g_pIndexBuffer);
	Device->SetFVF(FVF_SKYDORM_VERTEX3D);
	Device->SetTexture(0,Texture_GetTexture(Texture));
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,VertexNum,0,(MESH_SKYDORM_GRID_HEIGHT * MESH_SKYDORM_GRID_WIDTH + (MESH_SKYDORM_GRID_HEIGHT -1) * 2) * 2);
}

void MeshSkyDome_Finalize()
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