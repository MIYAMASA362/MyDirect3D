//
//	CCamera.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/17
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include<d3dx9.h>
#include"common.h"
#include"input.h"
#include"System.h"

//classs
#include"CGameObject.h"
#include"CCamera.h"

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================
ACamera*  ACamera::pMainCamera = NULL;

//===============================================
//	ACamera
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
ACamera::ACamera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov):transform(Position)
{
	this->at = At;
	this->atDistance = AtDistance;
	this->fov = fov;

	//�O
	this->transform.forward = CAMERA_FORWARD;
	D3DXVec3Normalize(&this->transform.forward, &this->transform.forward);

	//�E
	D3DXVec3Cross(&this->transform.right, &this->transform.forward, &this->transform.up);
	D3DXVec3Normalize(&this->transform.right, &this->transform.right);
}

//-------------------------------------
//	���C���J�����̎擾
//-------------------------------------
ACamera* ACamera::Get_Main()
{
	return pMainCamera;
}

//-------------------------------------
//	�`��
//-------------------------------------
bool ACamera::Begin()
{
	if (pMainCamera == NULL)
	{
		MessageBox(*System_GethWnd(), "���C���J�������ݒ肳��Ă��܂���B", "CCamera.cpp", MB_OK);
		DestroyWindow(*System_GethWnd());
		return false;
	}

	//------------------------------------
	//	�r���[�ϊ��s��
	//------------------------------------
	D3DXMATRIX mtxView;							//�r���[�ϊ��s��
	D3DXMatrixLookAtLH(&mtxView, &pMainCamera->transform.Position, &pMainCamera->at, &pMainCamera->transform.up);	//�ϊ�
	System_GetDevice()->SetTransform(D3DTS_VIEW, &mtxView);		//�f�o�C�X�֓o�^
	pMainCamera->MtxView = mtxView;

	//------------------------------------
	//	�v���W�F�N�V�����ϊ��s��
	//------------------------------------
	D3DXMATRIX mtxProjection;		//�v���W�F�N�V�����ϊ��s��
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fov�͉�p�@�ϊ�
	System_GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);	//�f�o�C�X�֓o�^

	return true;
}

//-------------------------------------
//	View�s��擾
//-------------------------------------
D3DXMATRIX ACamera::Get_ViewMatrix()
{
	return pMainCamera->MtxView;
}

//-------------------------------------
//	���C���J�����ɐݒ�
//-------------------------------------
void ACamera::Set_Main()
{
	pMainCamera = this;
}

//===============================================
//	Camera
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Camera::Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov):ACamera(Position,At,AtDistance,fov)
{
	
}

//-------------------------------------
//	�X�V
//-------------------------------------
void Camera::Update()
{

}

//===============================================
//	OperationCamera
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
OperationCamera::OperationCamera(D3DXVECTOR3 Position, D3DXVECTOR3 At,float AtDistance,float fov):ACamera(Position,At,AtDistance,fov)
{
	this->Speed = CAMERA_INITIALSPEED;
	this->SpeedMag = 1.0f;
}

//-------------------------------------
//	�X�V
//-------------------------------------
void OperationCamera::Update()
{
	//------------------------------------
	//	�J����
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
			D3DXVec3TransformNormal(&this->transform.forward, &this->transform.forward, &mtxRotation);	//�x�N�g�����W�ϊ�
			D3DXVec3TransformNormal(&this->transform.right, &this->transform.right, &mtxRotation);
			D3DXVec3Cross(&this->transform.up, &this->transform.right, &this->transform.forward);

			D3DXMatrixIdentity(&mtxRotation);
			AxisVec = this->transform.right;
			D3DXMatrixRotationAxis(&mtxRotation,&AxisVec,Mouse_IsAccelerationY() * 0.001f);
			D3DXVec3TransformNormal(&this->transform.forward, &this->transform.forward, &mtxRotation);	//�x�N�g�����W�ϊ�
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
			D3DXVec3TransformNormal(&this->transform.forward, &this->transform.forward, &mtxRotation);	//�x�N�g�����W�ϊ�
			D3DXVec3TransformNormal(&this->transform.right, &this->transform.right, &mtxRotation);
			D3DXVec3Cross(&this->transform.up, &this->transform.right, &this->transform.forward);

			D3DXMatrixIdentity(&mtxRotation);
			D3DXMatrixRotationAxis(&mtxRotation, &this->transform.right, Mouse_IsAccelerationY() * -0.001f);
			D3DXVec3TransformNormal(&this->transform.forward, &this->transform.forward, &mtxRotation);	//�x�N�g�����W�ϊ�
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

