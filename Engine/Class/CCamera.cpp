//
//	CCamera.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/17
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include<d3dx9.h>
#include"common.h"
#include"input.h"
#include"System.h"

//classs
#include"CGameObject.h"
#include"CCamera.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================
ACamera*  ACamera::pMainCamera = NULL;

//===============================================
//	ACamera
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
ACamera::ACamera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov):transform(Position)
{
	this->at = At;
	this->atDistance = AtDistance;
	this->fov = fov;

	//前
	this->transform.forward = CAMERA_FORWARD;
	D3DXVec3Normalize(&this->transform.forward, &this->transform.forward);

	//右
	D3DXVec3Cross(&this->transform.right, &this->transform.forward, &this->transform.up);
	D3DXVec3Normalize(&this->transform.right, &this->transform.right);
}

//-------------------------------------
//	メインカメラの取得
//-------------------------------------
ACamera* ACamera::Get_Main()
{
	return pMainCamera;
}

//-------------------------------------
//	描画
//-------------------------------------
bool ACamera::Begin()
{
	if (pMainCamera == NULL)
	{
		MessageBox(*System_GethWnd(), "メインカメラが設定されていません。", "CCamera.cpp", MB_OK);
		DestroyWindow(*System_GethWnd());
		return false;
	}

	//------------------------------------
	//	ビュー変換行列
	//------------------------------------
	D3DXMATRIX mtxView;							//ビュー変換行列
	D3DXMatrixLookAtLH(&mtxView, &pMainCamera->transform.Position, &pMainCamera->at, &pMainCamera->transform.up);	//変換
	System_GetDevice()->SetTransform(D3DTS_VIEW, &mtxView);		//デバイスへ登録
	pMainCamera->MtxView = mtxView;

	//------------------------------------
	//	プロジェクション変換行列
	//------------------------------------
	D3DXMATRIX mtxProjection;		//プロジェクション変換行列
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fovは画角　変換
	System_GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);	//デバイスへ登録

	return true;
}

//-------------------------------------
//	View行列取得
//-------------------------------------
D3DXMATRIX ACamera::Get_ViewMatrix()
{
	return pMainCamera->MtxView;
}

//-------------------------------------
//	メインカメラに設定
//-------------------------------------
void ACamera::Set_Main()
{
	pMainCamera = this;
}

//===============================================
//	Camera
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Camera::Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov):ACamera(Position,At,AtDistance,fov)
{
	
}

//-------------------------------------
//	更新
//-------------------------------------
void Camera::Update()
{

}

//===============================================
//	OperationCamera
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
OperationCamera::OperationCamera(D3DXVECTOR3 Position, D3DXVECTOR3 At,float AtDistance,float fov):ACamera(Position,At,AtDistance,fov)
{
	this->Speed = CAMERA_INITIALSPEED;
	this->SpeedMag = 1.0f;
}

//-------------------------------------
//	更新
//-------------------------------------
void OperationCamera::Update()
{
	//------------------------------------
	//	カメラ
	//------------------------------------
	this->at = this->transform.forward * this->atDistance + this->transform.Position;

	D3DXVECTOR3 front = this->transform.forward;
	D3DXVECTOR3 right = this->transform.right;

	if(Keyboard_IsPress(DIK_LCONTROL))
	{
		if(Mouse_IsRightDown())
		{
			D3DXMATRIX mtxRotation;
			D3DXVECTOR3 AxisVec = this->at;
			AxisVec.x = 0;
			AxisVec.z = 0;
			D3DXMatrixRotationAxis(&mtxRotation,&AxisVec,Mouse_IsAccelerationX() * 0.001f);
			D3DXVec3TransformNormal(&this->transform.forward, &this->transform.forward, &mtxRotation);	//ベクトル座標変換
			D3DXVec3TransformNormal(&this->transform.right, &this->transform.right, &mtxRotation);
			D3DXVec3Cross(&this->transform.up, &this->transform.right, &this->transform.forward);

			D3DXMatrixIdentity(&mtxRotation);
			AxisVec = this->transform.right;
			D3DXMatrixRotationAxis(&mtxRotation,&AxisVec,Mouse_IsAccelerationY() * 0.001f);
			D3DXVec3TransformNormal(&this->transform.forward, &this->transform.forward, &mtxRotation);	//ベクトル座標変換
			D3DXVec3TransformNormal(&this->transform.right, &this->transform.right, &mtxRotation);
			D3DXVec3Cross(&this->transform.up, &this->transform.right, &this->transform.forward);
			D3DXMatrixTranslation(&mtxRotation,this->at.x,this->at.y,this->at.z);
			D3DXVec3TransformNormal(&at,&at,&mtxRotation);
			
		}

		this->transform.Position = at - this->transform.forward * this->atDistance;
	}
	else
	{
		if(Keyboard_IsPress(DIK_LSHIFT))
		{
			SpeedMag += 0.05f;
			SpeedMag = min(SpeedMag,20.0f);
		}
		else
		{
			SpeedMag = 1.0f;
		}

		if (Mouse_IsRightDown())
		{
			D3DXMATRIX mtxRotation;
			D3DXMatrixRotationY(&mtxRotation, Mouse_IsAccelerationX() * 0.001f);
			D3DXVec3TransformNormal(&this->transform.forward, &this->transform.forward, &mtxRotation);	//ベクトル座標変換
			D3DXVec3TransformNormal(&this->transform.right, &this->transform.right, &mtxRotation);
			D3DXVec3Cross(&this->transform.up, &this->transform.right, &this->transform.forward);

			D3DXMatrixIdentity(&mtxRotation);
			D3DXMatrixRotationAxis(&mtxRotation, &this->transform.right, Mouse_IsAccelerationY() * -0.001f);
			D3DXVec3TransformNormal(&this->transform.forward, &this->transform.forward, &mtxRotation);	//ベクトル座標変換
			D3DXVec3TransformNormal(&this->transform.right, &this->transform.right, &mtxRotation);
			D3DXVec3Cross(&this->transform.up, &this->transform.right, &this->transform.forward);

		}

		if (Keyboard_IsPress(DIK_W))
		{
			this->transform.Position += front * this->Speed * SpeedMag;
		}

		if (Keyboard_IsPress(DIK_S))
		{
			this->transform.Position -= front * this->Speed * SpeedMag;
		}

		if (Keyboard_IsPress(DIK_A))
		{
			this->transform.Position += right * this->Speed * SpeedMag;
		}

		if (Keyboard_IsPress(DIK_D))
		{
			this->transform.Position -= right * this->Speed * SpeedMag;
		}

		if (Keyboard_IsPress(DIK_Q))
		{
			this->transform.Position.y -= this->Speed * SpeedMag;
		}

		if (Keyboard_IsPress(DIK_E))
		{
			this->transform.Position.y += this->Speed * SpeedMag;
		}

		this->atDistance += Mouse_IsAccelerationZ() *0.005f;

		if (this->atDistance > 1.0f)
		{
			this->transform.Position -= this->transform.forward * Mouse_IsAccelerationZ() *0.005f;
		}
		else
		{
			this->atDistance = 1.0f;
		}
	}
	
	return;
}

