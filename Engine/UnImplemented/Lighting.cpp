//
//	Lighting.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/04
//===============================================
#include"Lighting.h"
#include"System.h"

//===============================================
//	グローバル変数
//===============================================
#define COLORVALUE_RGBA(r,g,b,a) D3DCOLORVALUE{r/255,g/255,b/255,a/255}

static D3DLIGHT9 g_DirectLight;
static D3DXVECTOR3 g_DirectLight_Direction;
static bool g_bMaterialEnable = false;				//マテリアルが有効か

//===============================================
//	初期化
//===============================================
void Lighting_Initialize()
{
	LPDIRECT3DDEVICE9 Device = System_GetDevice();

	//------------------------------------
	//	描画設定
	//------------------------------------
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//半透明処理をON
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//背景DSETのブレンド設定
	Device->SetRenderState(D3DRS_ZENABLE, TRUE);						//深度を適用

	//アルファテスト
	Device->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF,200);
	Device->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//テクスチャポリゴン透過処理

	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//------------------------------------
	//	ライティング
	//------------------------------------
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);	//ライティングをON/OFF

	ZeroMemory(&g_DirectLight, sizeof(g_DirectLight));
	g_DirectLight.Type = D3DLIGHT_DIRECTIONAL;

	g_DirectLight_Direction = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	D3DXVec3Normalize(&g_DirectLight_Direction, &g_DirectLight_Direction);

	g_DirectLight.Diffuse = COLORVALUE_RGBA(255,255,255,255);
	g_DirectLight.Direction = g_DirectLight_Direction;

	Device->SetLight(0, &g_DirectLight);
	Device->LightEnable(0, TRUE);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);	//法線ベクトルを単位ベクトル化：拡大・縮小の変化
	Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	//アンビエント
	Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(84, 84, 84, 255));
	Device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	g_bMaterialEnable = true;

	/*
		D3DMCS_COLOR1 頂点カラーをマテリアルの色にします。
		D3DMCS_MATERIAL マテリアルをマテリアルの色にします。

		提案1
		 ライトらかSetRenderStateの設定を消す。
		 キューブなどの描画にD3DMCS_COLOR1
		 モデルの描画にD3DMCS_MATERIAL

		提案2
		 どちらかをデフォルトを設定して
		 違うやつをやった後に、デフォルトに戻す
	
		提案3
		　全てをマテリアルにする
	*/
}

//===============================================
//	ライト設定
//===============================================
void Lighting_SetLight(BOOL bSet)
{
	System_GetDevice()->SetRenderState(D3DRS_LIGHTING, bSet);	//ライティングをON
}

//===============================================
//	マテリアルを無効
//===============================================
void Lighting_MaterialDisEnable()
{
	if (g_bMaterialEnable)
	{
		System_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
		System_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
		g_bMaterialEnable = false;
	}

	return;
}

//===============================================
//	マテリアルを有効
//===============================================
void Lighting_MatrialEnable()
{
	if (!g_bMaterialEnable)
	{
		System_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		System_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
		g_bMaterialEnable = true;
	}

	return;
}

