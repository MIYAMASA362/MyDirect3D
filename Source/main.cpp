//
//	Main.cpp
//		Author:HIROMASA IKEDA		Date:2018/10/22
//================================================
#include"common.h"
#include<time.h>
#include<math.h>
#include"System.h"
#include"input.h"

#include"Lighting.h"
#include"XModel.h"

#include"Billboard.h"

//Class
#include"CUI.h"
#include"CGameObject.h"
#include"CCamera.h"

#include"CTransform.h"

#include"WinSock.h"
#include"CAirplane.h"
#include"Grid.h"
#include"CBullet.h"

//Geometry
#include"MeshField_Ground.h"
#include"MeshField_Cylinder.h"
#include"MeshField_SkyDome.h"

//===============================================
//	�O���[�o���ϐ�
//===============================================

//�J����
static OperationCamera g_Camera(
	{0,5,5}
);

static CAirplane Airplane(
	&Transform(
		{ 0.0f,2.0f,0.0f },
		{ 0.005f,0.005f,0.005f },
		{ 0.0f, 0.0f, D3DXToRadian(60)}
	)
);

//=============================================================
//	����������
//=============================================================
void Main_Initialize(void)
{

	XModel::Load();

	//g_Camera.Set_Main();
	Airplane.Boarding();
	Billboard_Initialize();

	MeshField_Ground_Initialize();
	MeshCylinder_Initialize();
	MeshSkyDome_Initialize();
	//Grid_Initialize();
	
}


//=============================================================
//	�O �X�V����
//=============================================================
void Main_UpdateBegin(void)
{
	
	WinSock_Receiver();	//�f�[�^����M���܂��B
	
	Transform::ConvertReset();
	
	GameObject::g_Update();
	CBullet::g_Update();

	//g_Camera.transform = Airplane.transform;

	//	�J�����̌����ňړ�������
	//----------------------------------------------
	g_Camera.Update();
	
	
}

//=============================================================
//	�`�揈��
//=============================================================
void Main_Render(void)
{
	Camera::Begin();		//�`��J�n
	GameObject::g_Render();
	CBullet::g_Render();

	//Grid_Render();
	MeshSkyDome_Render(D3DXVECTOR3(0.0f, 0.0f, 0.0f),MeshCylinderTex);
	MeshField_Ground_Render(D3DXVECTOR3(0.0f,0.0f,0.0f), MeshFieldTex);
}


//=============================================================
//	�� ����
//=============================================================
void Main_UpdateEnd()
{

}

//=============================================================
//	�I������
//=============================================================
void Main_Finalize(void)
{
	BillBoard_Finalaize();
	MeshCylinder_Finalize();
	MeshField_Ground_Finalize();
	MeshSkyDome_Finalize();
	CBullet_Finalize();
}
