//
//	Geometry.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/18
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include"Geometry.h"
#include"System.h"

#include"Cube.h"
#include"Grid.h"
#include"MeshField_Ground.h"
#include"MeshField_Cylinder.h"
#include"MeshField_SkyDome.h"
//Class

//===============================================
//	�}�N����`		define
//===============================================

//===============================================
//	�O���[�o���ϐ�	global
//===============================================


//===============================================
//	�֐�			function
//===============================================

//-------------------------------------
//	������
//-------------------------------------
void Geometry_Initialize()
{
	Cube_Initialize();
	Grid_Initialize();
	MeshField_Ground_Initialize();
	MeshCylinder_Initialize();
	MeshSkyDome_Initialize();
}

//-------------------------------------
//	�X�V
//-------------------------------------
void Geometry_Update()
{

}

//-------------------------------------
//	�`��
//-------------------------------------
void Geometry_Render()
{
	Grid_Render();
}

//-------------------------------------
//	�I��
//-------------------------------------
void Geometry_Finalize()
{
	MeshCylinder_Finalize();
	MeshField_Ground_Finalize();
	MeshSkyDome_Finalize();
}

