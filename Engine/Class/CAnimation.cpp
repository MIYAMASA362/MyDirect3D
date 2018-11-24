//
//	CAnimation.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#include<d3dx9.h>
#include"CTransform.h"
#include"Animation.h"
#include"CAnimation.h"

//===============================================
//	Animation クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Animation::Animation()
{
	AnimaPatern = 0;
	MaxPatern = 0;
	YMaxPatern = 0;
	Waitframe = 0;
	Createframe = Animation_GetFrame();
}

Animation::Animation(int MaxPatern, int YMaxPatern, int Waitframe)
{
	AnimaPatern = 0;
	this->MaxPatern = MaxPatern;
	this->YMaxPatern = YMaxPatern;
	this->Waitframe = Waitframe;
	Createframe = Animation_GetFrame();
}