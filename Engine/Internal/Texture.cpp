//
//	Texture.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/13
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include<d3dx9.h>
#include"Texture.h"
#include"System.h"

//===============================================
//	構造体
//===============================================

//-------------------------------------
//	テクスチャデータ
//-------------------------------------
typedef struct TEXTUREDATA_INDEX
{
	int TexName;								//テクスチャ名
 	const char FileAddress[TEXTURE_FILENAME_MAX];		//アドレス
	UINT width;									//テクスチャ幅
	UINT height;								//テクスチャ高さ
}TEXTUREDATA_INDEX;

//===============================================
//	グローバル変数
//===============================================
#if !defined(DISABLE_TEXTURE)

//-------------------------------------
//	テクスチャ
//-------------------------------------
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_NAME_END];

//-------------------------------------
//	テクスチャインデックス *サイズは自動取得
//-------------------------------------
static TEXTUREDATA_INDEX Texture_Index[] = 
{
	{CubeTexture,"Texture/tex.png"},
	{BillBoardTex,"Texture/bullet000.png"},
	{MeshFieldTex,"Texture/MeshGround.jpg"},
	{MeshCylinderTex,"Texture/skytex1.jpeg"},
	{Billboard_Burst,"Texture/bomb.png"},
	{Billboard_Shadow,"Texture/shadow000.jpg"},
	{Billboard_Wall,"Texture/KAZTDSCF8777_TP_V.jpg"}
};

#endif

//===============================================
//	関数
//===============================================
void Texture_Load(TEXTUREDATA_INDEX* pTextureData_Index, LPDIRECT3DTEXTURE9* plpTexture, const int nListEnd);

//-------------------------------------
//	テクスチャ初期化
//-------------------------------------
void Texture_Initialize()
{
#if !defined(DISABLE_TEXTURE)

	Texture_Load(&Texture_Index[0],&g_pTextures[0],TEXTURE_NAME_END);

#endif
}

//-------------------------------------
//	テクスチャの読み込み [先頭ファイルデータ] [先頭テクスチャ] [テクスチャ名の最終番目]
//-------------------------------------
void Texture_Load(TEXTUREDATA_INDEX *pTextureData_Index,LPDIRECT3DTEXTURE9 *plpTexture, const int nListEnd)
{
	HRESULT hr;
	char ErrorText[256] = {};
	int failded_Count = 0;

	for (int i = 0; i < nListEnd; i++)
	{
		D3DXIMAGE_INFO Texture_Info;	//画像データ情報

		//読み込みが失敗した時にはg_pTexture[i]にnullが置かれる
		hr = D3DXCreateTextureFromFile(System_GetDevice(), pTextureData_Index->FileAddress, plpTexture);

		if (FAILED(hr))
		{
			//エラーの表示
			strcat(ErrorText, pTextureData_Index->FileAddress);
			strcat(ErrorText, "\n");
			failded_Count++;
		}
		else
		{
			//画像データ取得
			D3DXGetImageInfoFromFile(pTextureData_Index->FileAddress, &Texture_Info);
			pTextureData_Index->height = Texture_Info.Height;
			pTextureData_Index->width = Texture_Info.Width;
		}

		plpTexture ++;
		pTextureData_Index ++;
	}

	//読み込みに失敗している
	if (failded_Count != 0)
	{
		MessageBox(*System_GethWnd(), ErrorText, "読み込み失敗", MB_OK);
		DestroyWindow(*System_GethWnd());
	}

	return;
}

//-------------------------------------
//	終了処理
//-------------------------------------
void Texture_Finalize() 
{
#if !defined(DISABLE_TEXTURE)
	for (int i = 0; i < TEXTURE_NAME_END; i++)
	{
		if (g_pTextures[i] != NULL)
		{
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
#endif
}

//-------------------------------------
//	テクスチャポインタの取得
//-------------------------------------
LPDIRECT3DTEXTURE9 Texture_GetTexture(int index) 
{
#if !defined(DISABLE_TEXTURE)
	return g_pTextures[index];
#else
	return NULL;
#endif
}

//-------------------------------------
//	テクスチャ幅の取得
//-------------------------------------
int Texture_GetWidth(int index) 
{
#if !defined(DISABLE_TEXTURE)
	return Texture_Index[index].width;
#else
	return 0;
#endif
}

//-------------------------------------
//	テクスチャ縦の取得
//-------------------------------------
int Texture_GetHeight(int index) 
{
#if !defined(DISABLE_TEXTURE)
	return Texture_Index[index].height;
#else
	return 0;
#endif
}
