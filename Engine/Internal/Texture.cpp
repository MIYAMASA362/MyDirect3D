//
//	Texture.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/13
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include<d3dx9.h>
#include"Texture.h"
#include"System.h"

//===============================================
//	�\����
//===============================================

//-------------------------------------
//	�e�N�X�`���f�[�^
//-------------------------------------
typedef struct TEXTUREDATA_INDEX
{
	int TexName;								//�e�N�X�`����
 	const char FileAddress[TEXTURE_FILENAME_MAX];		//�A�h���X
	UINT width;									//�e�N�X�`����
	UINT height;								//�e�N�X�`������
}TEXTUREDATA_INDEX;

//===============================================
//	�O���[�o���ϐ�
//===============================================
#if !defined(DISABLE_TEXTURE)

//-------------------------------------
//	�e�N�X�`��
//-------------------------------------
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_NAME_END];

//-------------------------------------
//	�e�N�X�`���C���f�b�N�X *�T�C�Y�͎����擾
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
//	�֐�
//===============================================
void Texture_Load(TEXTUREDATA_INDEX* pTextureData_Index, LPDIRECT3DTEXTURE9* plpTexture, const int nListEnd);

//-------------------------------------
//	�e�N�X�`��������
//-------------------------------------
void Texture_Initialize()
{
#if !defined(DISABLE_TEXTURE)

	Texture_Load(&Texture_Index[0],&g_pTextures[0],TEXTURE_NAME_END);

#endif
}

//-------------------------------------
//	�e�N�X�`���̓ǂݍ��� [�擪�t�@�C���f�[�^] [�擪�e�N�X�`��] [�e�N�X�`�����̍ŏI�Ԗ�]
//-------------------------------------
void Texture_Load(TEXTUREDATA_INDEX *pTextureData_Index,LPDIRECT3DTEXTURE9 *plpTexture, const int nListEnd)
{
	HRESULT hr;
	char ErrorText[256] = {};
	int failded_Count = 0;

	for (int i = 0; i < nListEnd; i++)
	{
		D3DXIMAGE_INFO Texture_Info;	//�摜�f�[�^���

		//�ǂݍ��݂����s�������ɂ�g_pTexture[i]��null���u�����
		hr = D3DXCreateTextureFromFile(System_GetDevice(), pTextureData_Index->FileAddress, plpTexture);

		if (FAILED(hr))
		{
			//�G���[�̕\��
			strcat(ErrorText, pTextureData_Index->FileAddress);
			strcat(ErrorText, "\n");
			failded_Count++;
		}
		else
		{
			//�摜�f�[�^�擾
			D3DXGetImageInfoFromFile(pTextureData_Index->FileAddress, &Texture_Info);
			pTextureData_Index->height = Texture_Info.Height;
			pTextureData_Index->width = Texture_Info.Width;
		}

		plpTexture ++;
		pTextureData_Index ++;
	}

	//�ǂݍ��݂Ɏ��s���Ă���
	if (failded_Count != 0)
	{
		MessageBox(*System_GethWnd(), ErrorText, "�ǂݍ��ݎ��s", MB_OK);
		DestroyWindow(*System_GethWnd());
	}

	return;
}

//-------------------------------------
//	�I������
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
//	�e�N�X�`���|�C���^�̎擾
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
//	�e�N�X�`�����̎擾
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
//	�e�N�X�`���c�̎擾
//-------------------------------------
int Texture_GetHeight(int index) 
{
#if !defined(DISABLE_TEXTURE)
	return Texture_Index[index].height;
#else
	return 0;
#endif
}
