//
//	CTexture.h
//		Author:HIROMASA IKEDA	DATE:2018/09/26
//===============================================
#pragma once
#ifndef CTEXTURE_H
#define CTEXTURE_H

#include<d3dx9.h>
#include"Texture.h"

//===============================================
//	Class	�N���X
//===============================================

namespace TEXTURE
{
	//-------------------------------------
	//	���ۃN���X
	//-------------------------------------
	class ATexture
	{
	public:
		ATexture();
	};
}

//-------------------------------------
//	�e�N�X�`��
//-------------------------------------
class Texture
{
private:
	int Tex_Width;				//���e�N�X�`���̕�
	int Tex_Height;				//���e�N�X�`���̍���
public:
	int Texture_index;			//�e�N�X�`����
	TEXCOORD TexCoord;			//�e�N�X�`�����W
	TEXSCALE TexScale;			//�e�N�X�`���T�C�Y

	int GetWidth();				//���擾
	int GetHeight();			//�����擾
	TEXSCALE GetTexScale();		//�T�C�Y�擾

public:
	//�R���X�g���N�^
	Texture():Texture(TEXTURE_NONE, { 0,0 }, { 0,0 }){};
	Texture(int Texture_index, TEXCOORD TexCoord, TEXSCALE TexScale);
};


#endif // !CTEXTURE_H

