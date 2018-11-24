//
//	MeshField_Cylinder.h
//		Author:IKEDA HIROMASA	DATE:2018/11/12
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef MESHFIELD_CYLINDER_H
#define MESHFIELD_CYLINDER_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>

#include"Texture.h"

//================================================
//	�}�N����`	define
//================================================
#define FVF_MESHFIELD (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

#define MESH_CYLINDER_HEIGHT (50)	//����
#define MESH_CYLINDER_RADIUS (40.0f)	//���a

#define MESH_CYLINDER_GRID_WIDTH (100)	//���O���b�h��
#define MESH_CYLINDER_GRID_HEIGHT (10)	//�c�O���b�h��

#define MESH_ANGLE ((2*M_PI)/MESH_CYLINDER_GRID_WIDTH)	//1�O���b�h�p�x
#define MESH_HEIGHT (MESH_CYLINDER_HEIGHT / MESH_CYLINDER_GRID_HEIGHT)	//1�O���b�h����


//================================================
//	�񋓌^		enum
//================================================
struct  MeshFieldVertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR2 TexCoord;
};

//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�֐�		function
//================================================
void MeshCylinder_Initialize();
void MeshCylinder_Render(const D3DXVECTOR3 Center, TEXTURE_NAME Texture);
void MeshCylinder_Finalize();
D3DXVECTOR3 MeshCylinder_GetCenter();
#endif