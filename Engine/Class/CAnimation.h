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
//	Animation : 2D専用　クラス	
//===============================================
class Animation
{
private:

public:
	int AnimaPatern;			//アニメーション
	int MaxPatern;				//最大アニメーション
	int YMaxPatern;				//横最大アニメーション
	int Waitframe;				//アニメーション速度
	int Createframe;			//生成された時のフレーム

public:
	//コンストラクタ
	Animation();
	Animation(int MaxPatern,int YMaxPatern,int Waitframe);
};

#endif // !ANIMETIONCLASS_H

