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

//Geometry
#include"MeshField_Ground.h"
#include"MeshField_Cylinder.h"
#include"MeshField_SkyDome.h"

//===============================================
//	グローバル変数
//===============================================

//カメラ
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

/*
static CAirplane Airplane_Sub1(
	&Transform(
		{ 2.0f,2.7f,5.0f },
		{ 0.005f,0.005f,0.005f },
		{ 0.0f,0.0f,D3DXToRadian(40) }
	)
);

static CAirplane Airplane_Sub2(
	&Transform(
		{ -2.4f,2.7f,5.0f },
		{ 0.005f,0.005f,0.005f },
		{ 0.0f,0.0f,D3DXToRadian(60) }
	)
);

static GameObject Tank(
	&Transform(
		{3.0f,0.75f,-2.0f},
		{1.5f,1.5f,1.5f}
	)
);

static GameObject Tree1(
	&Transform(
		{3.8f,0.0f,0.0f},
		{3.0f,3.0f,3.0f}
	)
);

static GameObject Tree2(
	&Transform(
		{ 5.0f,0.0f,3.0f },
		{ 3.0f,3.0f,3.0f }
	)
);
static GameObject Tree3(
	&Transform(
		{ 6.0f,0.0f,1.0f },
		{ 3.0f,3.0f,3.0f }
	)
);


static GameObject Airplane_Obj1(
	&Transform({ 0.0f,0.6f,5.0f },{0.05f, 0.05f, 0.05f}, {0.0f,0.0f,0.0f})
);
*/

//=============================================================
//	初期化処理
//=============================================================
void Main_Initialize(void)
{

	XModel::Load();

	g_Camera.Set_Main();
	//Airplane.Boarding();
	Billboard_Initialize();

	MeshField_Ground_Initialize();
	MeshCylinder_Initialize();
	MeshSkyDome_Initialize();
	//Grid_Initialize();

	/*
	Airplane_Obj1.render.SetMesh(new CXModelName(XModel::AIRPLANE_MODEL));
	Tank.render.SetMesh(new CXModelName(XModel::TANK));
	Tree1.render.SetMesh(new CXModelName(XModel::TREE));
	Tree2.render.SetMesh(new CXModelName(XModel::TREE));
	Tree3.render.SetMesh(new CXModelName(XModel::TREE));
	*/
	
}


//=============================================================
//	前 更新処理
//=============================================================
void Main_UpdateBegin(void)
{
	
	WinSock_Receiver();	//データを受信します。
	
	Transform::ConvertReset();
	
	GameObject::g_Update();

	if(Keyboard_IsPress(DIK_1))
	{
		Airplane.transform.rotation.z += D3DXToRadian(1);
	}

	if (Keyboard_IsPress(DIK_2))
	{
		Airplane.transform.rotation.x += D3DXToRadian(1);
	}

	if (Keyboard_IsPress(DIK_3))
	{
		Airplane.transform.rotation.y += D3DXToRadian(1);
	}

	if(Keyboard_IsPress(DIK_U))
	{
		Airplane.transform.position -= Airplane.transform.forward * 0.1f;
	}

	g_Camera.transform = Airplane.transform;

	//	カメラの向きで移動するやつ
	//----------------------------------------------
	g_Camera.Update();
	
}

//=============================================================
//	描画処理
//=============================================================
void Main_Render(void)
{
	Camera::Begin();		//描画開始
	GameObject::g_Render();

	//Grid_Render();
	MeshSkyDome_Render(D3DXVECTOR3(0.0f, 0.0f, 0.0f),MeshCylinderTex);
	MeshField_Ground_Render(D3DXVECTOR3(0.0f,0.0f,0.0f), MeshFieldTex);
}


//=============================================================
//	後 処理
//=============================================================
void Main_UpdateEnd()
{

}

//=============================================================
//	終了処理
//=============================================================
void Main_Finalize(void)
{
	BillBoard_Finalaize();
	MeshCylinder_Finalize();
	MeshField_Ground_Finalize();
	MeshSkyDome_Finalize();
}
