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
#include"Animation.h"
#include"CBurst.h"

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
		{ 0.0f, 0.0f, 0.0f}
	)
);

//=============================================================
//	����������
//=============================================================
void Main_Initialize(void)
{
	Animation_Initialize();
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
	Animation_Update();
	WinSock_Receiver();	//�f�[�^����M���܂��B
	
	Transform::ConvertReset();
	
	GameObject::g_Update();
	ABillboard::g_Update();
	CBullet::g_Update();
	CBurst::g_Update();

	//g_Camera.transform = Airplane.transform;

	//	�J�����̌����ňړ�������
	//----------------------------------------------
	g_Camera.Update();

}
static Texture texture(Billboard_Burst, { 0,0 }, { 128,128 });
static Animation animation(18, 6, 4);
//=============================================================
//	�`�揈��
//=============================================================
void Main_Render(void)
{

	MeshSkyDome_Render(Airplane.transform.Position, MeshCylinderTex);
	MeshField_Ground_Render(D3DXVECTOR3(0.0f, 0.0f, 0.0f), MeshFieldTex);
	BillBoardShadow_Create(Airplane.transform.Position, { 1.0f,1.0f,1.0f });
	CBurst::g_Render();

	Camera::Begin();		//�`��J�n
	GameObject::g_Render();
	ABillboard::g_Render();
	CBullet::g_Render();
	

	//Grid_Render();

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
