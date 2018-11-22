//
//	CTexture.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#include<d3dx9.h>
#include"Texture.h"
#include"CTexture.h"

//===============================================
//	Texture �N���X
//===============================================

//-------------------------------------
//	Texture()
//-------------------------------------
Texture::Texture(int Texture_index, TEXCOORD TexCoord, TEXSCALE TexScale)
{
	this->Texture_index = Texture_index;
	this->TexCoord = TexCoord;
	this->TexScale = TexScale;
	if(Texture_index == TEXTURE_NONE)
	{
		Tex_Width = 0;
		Tex_Height = 0;
	}
	else
	{
		Tex_Width = Texture_GetWidth(Texture_index);
		Tex_Height = Texture_GetHeight(Texture_index);
	}
}

//-------------------------------------
//	�e�N�X�`���̕����擾
//-------------------------------------
int Texture::GetWidth()
{
	return Tex_Width;
}

//-------------------------------------
//	�e�N�X�`���̍����擾
//-------------------------------------
int Texture::GetHeight()
{
	return Tex_Height;
}

//-------------------------------------
//	�e�N�X�`���̃T�C�Y�擾
//-------------------------------------
TEXSCALE Texture::GetTexScale()
{
	return{ Tex_Width,Tex_Height };
}