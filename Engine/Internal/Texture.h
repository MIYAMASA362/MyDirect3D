//
//	Texture.h
//		Auther:HIROMASA IKEDA	Date:2018/09/13
//===============================================
#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include<d3dx9.h>
#include"common.h"

//===============================================
//	�}�N����`
//===============================================
#define TEXTURE_FILENAME_MAX (64)

//===============================================
//	��
//===============================================

//-------------------------------------
//	�e�N�X�`�������X�g
//-------------------------------------
typedef enum TEXTURE_NAME
{
	CubeTexture,
	BillBoardTex,
	MeshFieldTex,
	MeshCylinderTex,
	TEXTURE_NAME_END,	//�e�N�X�`���I���
	TEXTURE_NONE		//�w�薳���ꍇ
}TEXTURE_NAME;

//===============================================
//	�\����
//===============================================

//-------------------------------------
//	TexScale
//-------------------------------------
typedef struct TEXSCALE
{
	int width;
	int height;
}TEXSCALE;

//-------------------------------------
//	TexCoord
//-------------------------------------
typedef struct TEXCOORD
{
	int x;
	int y;
}TEXCOORD;

//===============================================
//	�֐�
//===============================================

void Texture_Initialize();							//�e�N�X�`��������
void Texture_Finalize();							//�e�N�X�`���I��

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index);	//�e�N�X�`���|�C���^�擾
int Texture_GetWidth(int index);					//�e�N�X�`�����擾 
int Texture_GetHeight(int index);					//�e�N�X�`�������擾

#endif
