//
//	CRender.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
#include<d3dx9.h>
#include<math.h>
#include<vector>

#include"CTransform.h"
#include"CRender.h"
#include"System.h"
#include"Texture.h"
#include"Sprite.h"
#include"Animation.h"

#include"Cube.h"
#include"CMesh.h"

//===============================================
//	Render3D�@�N���X
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Render3D::Render3D()
{
	pModel = new CStandardMesh();
	this->bRender = true;
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
Render3D::~Render3D()
{
	if(pModel != NULL)
	{
		delete pModel;
		pModel = NULL;
	}
}

//-------------------------------------
//	�`�悷��
//-------------------------------------
void Render3D::Begin(Transform* pTransform)
{
	if (pModel == NULL) return;

	System_GetDevice()->SetTransform(D3DTS_WORLD, &pTransform->Convert());

	pModel->begin();		//���f���̕`��
}

//-------------------------------------
//	���f���̐ݒ�
//-------------------------------------
void Render3D::SetMesh(AMesh* pModel)
{
	delete this->pModel;
	this->pModel = pModel;
}

//===============================================
//	Render2D �N���X
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Render2D::Render2D()
{
	pTransform = NULL;
	pTexture = NULL;
	pAnimation = NULL;
}

//-------------------------------------
//	�R���X�g���N�^	�|�C���^�^
//-------------------------------------
Render2D::Render2D(Transform2* pTransform, Texture* pTexture)
{
	this->pTransform = pTransform;
	this->pTexture = pTexture;
	pAnimation = NULL;
}

Render2D::Render2D(Transform2* pTransform, Texture* pTexture, Animation* pAnimation)
{
	this->pTransform = pTransform;
	this->pTexture = pTexture;
	this->pAnimation = pAnimation;
}

//-------------------------------------
//	�`��@�X�v���C�g
//-------------------------------------
bool Render2D::Begin(RENDER2D_TYPE R2D_TYPE)
{
	if (pTransform == NULL || pTexture == NULL) return false;

	switch (R2D_TYPE)
	{
	case R2D_PORIGON:
		Render2D_Porigon(pTransform);
		break;
	case R2D_RORIGON_ROTATE:
		Render2D_Porigon_Rotate(pTransform);
		break;
	case R2D_TEXTURE_SIZE:
		Render2D_Texture_Size(pTransform, pTexture);
		break;
	case R2D_TEXTURE_FILL:
		Render2D_Texture_Fill(pTransform, pTexture);
		break;
	case R2D_TEXTURE_CLIP:
		Render2D_Texture_Clip(pTransform, pTexture);
		break;
	case R2D_SPRITE:
		Render2D_Sprite(pTransform, pTexture);
		break;
	case R2D_SPRITE_ROTATE:
		Render2D_Sprite_Rotate(pTransform, pTexture);
		break;
	default:
		return false;
	}

	return true;
}

//-------------------------------------
//	�`��@�X�v���C�g�A�j���[�V����
//-------------------------------------
bool Render2D::Begin(RENDER2DANIMA_TYPE R2DA_TYPE)
{
	if (pTransform == NULL || pTexture == NULL || pAnimation == NULL) return false;

	switch (R2DA_TYPE)
	{
	case R2DA_NOLOOP:
		Animation_NoLoop(pTransform, pTexture, pAnimation);
		break;
	case R2DA_LOOP:
		Animation_Loop(pTransform, pTexture, pAnimation);
		break;
	case R2DA_LOOP_ROTATE:
		Animation_Loop_Rotate(pTransform, pTexture, pAnimation);
		break;
	default:
		return false;
	}

	return true;
}



