//
//	MeshField_Ground.h
//		Author:HIROMASA IKEDA	DATE:2018/10/25
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef MESHFIELD_GROUND_H
#define MESHFIELD_GROUND_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include"Texture.h"

//================================================
//	�}�N����`	define
//================================================
#define MESHFIELD_GRIDNUM_WIDTH (50)		//�O���b�h����(�l�p�|���S����)
#define MESHFIELD_GRIDNUM_DEPTH (50)		//�O���b�h���s����(�l�p�|���S����)

#define MESHFIELD_SIZE_WIDTH (100)			//�T�C�Y��
#define MESHFIELD_SIZE_DEPTH (100)			//�T�C�Y���s��

//���_�n
#define FVF_MESHFIELD_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================
struct MeshFieldVertex3D
{
	D3DXVECTOR3 Position;	//�ʒu
	D3DXVECTOR3 Normal;		//�@��
	D3DCOLOR Color;			//�F
	D3DXVECTOR2 TexCoord;	//�e�N�X�`��
};

//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�֐�		function
//================================================
void MeshField_Ground_Initialize();
void MeshField_Ground_Render(const D3DXVECTOR3 Center, TEXTURE_NAME Texture);
void MeshField_Ground_Finalize();



#endif