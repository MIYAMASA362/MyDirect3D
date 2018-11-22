//
//	Lighting.h
//		Author:HIROMASA IKEDA	DATE:2018/10/04
//===============================================
#pragma once
#ifndef LIGHTING_H
#define LIGHTING_H

#include<d3dx9.h>

//===============================================
//	�֐�
//===============================================
void Lighting_Initialize();
void Lighting_SetLight(BOOL bSet);
void Lighting_MaterialDisEnable();	//�}�e���A������
void Lighting_MatrialEnable();		//�}�e���A���L��

#endif // !LIGHTING_H

