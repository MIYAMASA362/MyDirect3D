//
//	CAnimation.h
//		Author:HIROMASA IKEDA		DATE:2018/09/28
//===============================================
#pragma once
#ifndef ANIMATIONCLASS_H
#define ANIMATIONCLASS_H

#include"common.h"
#include"Texture.h"
#include"CTransform.h"

//===============================================
//	Animation : 2D��p�@�N���X	
//===============================================
class Animation
{
private:

public:
	int AnimaPatern;			//�A�j���[�V����
	int MaxPatern;				//�ő�A�j���[�V����
	int YMaxPatern;				//���ő�A�j���[�V����
	int Waitframe;				//�A�j���[�V�������x
	int Createframe;			//�������ꂽ���̃t���[��

public:
	//�R���X�g���N�^
	Animation();
	Animation(int MaxPatern,int YMaxPatern,int Waitframe);
};

#endif // !ANIMETIONCLASS_H

