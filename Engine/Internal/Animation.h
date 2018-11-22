//
//	Animetion.h
//		USER:HIROMASA IKEDA		DATE:2018/09/28
//===============================================
#pragma once
#ifndef ANIMETION_H
#define ANIMETION_H

#include<d3dx9.h>

#include"common.h"
#include"CTransform.h"
#include"Texture.h"
#include"CTexture.h"
#include"CAnimation.h"

//===============================================
//	関数宣言	
//===============================================
void Animation_Initialize();	
void Animation_Update();
int Animation_GetFrame();

bool Animation_NoLoop(Transform2* pTransform, Texture* pTexture, Animation* pAnimation);		//ループしない
void Animation_Loop(Transform2* pTransform, Texture* pTexture, Animation* pAnimation);			//ループする
void Animation_Loop_Rotate(Transform2* pTransform, Texture* pTexture, Animation* pAnimation);	//ループ回転する

void Animation_Score(Transform2* pTransform, Texture* pTexture, Animation* pAnimation, int Score, bool bLeft, bool bZero, int digitNum);	//スコア

#endif

