//
//	Lighting.h
//		Author:HIROMASA IKEDA	DATE:2018/10/04
//===============================================
#pragma once
#ifndef LIGHTING_H
#define LIGHTING_H

#include<d3dx9.h>

//===============================================
//	関数
//===============================================
void Lighting_Initialize();
void Lighting_SetLight(BOOL bSet);
void Lighting_MaterialDisEnable();	//マテリアル無効
void Lighting_MatrialEnable();		//マテリアル有効

#endif // !LIGHTING_H

