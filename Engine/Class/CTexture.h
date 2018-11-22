//
//	CTexture.h
//		Author:HIROMASA IKEDA	DATE:2018/11/22
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
	//==============================================
	//	�񋓌^
	//==============================================

	const enum Name
	{
		NAME_END,	//�e�N�X�`���ŏI�Ԗ�
		NONE		//�w��Ȃ�
	};

	//==============================================
	//	�\����
	//==============================================
	
	struct Data
	{
		LPDIRECT3DTEXTURE9 texture;	//�e�N�X�`��
		UINT width;					//��
		UINT height;				//����
	};

	struct Path
	{
		Name name;					//�e�N�X�`����
		const char Address[60];		//�t�@�C���A�h���X
	};

	//==============================================
	//	�O���[�o���ϐ�
	//==============================================

	static Path path[] =
	{
		{NONE,""}
	};

	//==============================================
	//	�N���X
	//==============================================

	//-------------------------------------
	//	���ۃN���X
	//-------------------------------------
	class ATexture
	{
	public:
		Name name;			//�e�N�X�`����
		D3DXVECTOR2 Coord;	//���W(����)
		D3DXVECTOR2 Scale;	//�T�C�Y
	public:
		ATexture();
	};

	//------------------------------------
	//	�e�N�X�`���N���X
	//------------------------------------
	class CTexture :public ATexture
	{
	public:

	public:
		CTexture();
	};

	//==============================================
	//	�֐�
	//==============================================
	void Load();
	void Finalize();
	LPDIRECT3DTEXTURE9 Get(Name name);
	UINT Get_Width(Name name);
	UINT Get_Height(Name name);
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

