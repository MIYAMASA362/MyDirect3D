//
//	Billboard.cpp
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
#include"System.h"
#include"CCamera.h"
#include"Texture.h"

//Class
#include"CTransform.h"

//===============================================
//	マクロ定義		define
//===============================================
#define BILLBORAD_MAX (20)	//最大数
#define FVF_BILLBOARD (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

struct BillboardVertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;	
	D3DXVECTOR2 TexCoord;
	
};


//===============================================
//	グローバル変数	global
//===============================================
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;

static BillboardVertex* g_pBillboard_Vertex = NULL;

static D3DMATERIAL9 g_Material = {};

static BillboardVertex Billboard[4] = 
{
	{ { -0.5f,0.5f,0.0f  },{ 0.0f,0.0f,-1.0f },{ 0.0f,0.0f } },
	{ {  0.5f,0.5f,0.0f  },{ 0.0f,0.0f,-1.0f },{ 1.0f,0.0f } },
	{ { -0.5f,-0.5f,0.0f },{ 0.0f,0.0f,-1.0f },{ 0.0f,1.0f } },
	{ {  0.5f,-0.5f,0.0f },{ 0.0f,0.0f,-1.0f },{ 1.0f,1.0f } }
};

//===============================================
//	関数			function
//===============================================

//-------------------------------------
//	初期化処理
//-------------------------------------
void Billboard_Initialize()
{
	g_Material.Diffuse = g_Material.Ambient = { 1.0f,1.0f,1.0f,1.0f };

	System_GetDevice()->CreateVertexBuffer(
		sizeof(BillboardVertex)* 4,
		D3DUSAGE_WRITEONLY,
		FVF_BILLBOARD,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);

	g_pVertexBuffer->Lock(0, 0, (void**)&g_pBillboard_Vertex, 0);

	memcpy(&g_pBillboard_Vertex[0],&Billboard[0],sizeof(BillboardVertex) * 4);

	g_pVertexBuffer->Unlock();
}

//-------------------------------------
//	逆行列
//-------------------------------------
inline D3DXMATRIX InvMatrix()
{
	D3DXMATRIX InvView;
	D3DXMatrixTranspose(&InvView, &Camera::Get_ViewMatrix());
	InvView._14 = 0.0f;
	InvView._24 = 0.0f;
	InvView._34 = 0.0f;
	return InvView;
}

//-------------------------------------
//	生成処理
//-------------------------------------
void BillBoard_Create(D3DXVECTOR3 position)
{
	D3DXMATRIX InvView = InvMatrix();

	D3DXMATRIX MtxTransform;
	D3DXMatrixTranslation(&MtxTransform,position.x,position.y,position.z);

	D3DXMATRIX MtxWorld;
	D3DXMatrixIdentity(&MtxWorld);
	MtxWorld *= InvView * MtxTransform;

	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	Device->SetTransform(D3DTS_WORLD,&MtxWorld);
	Device->SetMaterial(&g_Material);
	Device->SetTexture(0,Texture_GetTexture(BillBoardTex));

	Device->SetStreamSource(0,g_pVertexBuffer,0,sizeof(BillboardVertex));
	Device->SetFVF(FVF_BILLBOARD);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

}

void BillBoard_Create(Transform* pTransform)
{
	D3DXMATRIX InvView = InvMatrix();

	D3DXMATRIX MtxTransform;
	D3DXMatrixTranslation(&MtxTransform,  pTransform->Position.x,pTransform->Position.y, pTransform->Position.z);

	D3DXMATRIX MtxScaling;
	D3DXMatrixScaling(&MtxScaling,pTransform->Scale.x,pTransform->Scale.y,pTransform->Scale.z);

	D3DXMATRIX MtxWorld;
	D3DXMatrixIdentity(&MtxWorld);
	MtxWorld = InvView * MtxScaling *MtxTransform;

	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	Device->SetTransform(D3DTS_WORLD, &MtxWorld);
	Device->SetMaterial(&g_Material);
	Device->SetTexture(0, Texture_GetTexture(BillBoardTex));

	Device->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillboardVertex));
	Device->SetFVF(FVF_BILLBOARD);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-------------------------------------
//	終了処理
//-------------------------------------
void BillBoard_Finalaize()
{
	if(g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}