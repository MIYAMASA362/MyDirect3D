//
//	input.h
//		Author:HIROMASA IKEDA	DATE:2018/09/13
//===============================================
#ifndef INPUT_H
#define INPUT_H

#include<Windows.h>
#include<d3dx9.h>
#define INIGUID
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION (0x800) 
#endif // !DIRECTINPUT_VERSION

#include<dinput.h>

#include"common.h"

//===============================================
//	マクロ定義
//===============================================
//#define DISABLE_GAMEPAD		//ゲームパッドを無効化
//#define DISABLE_DS4			//DualShock4を無効化
//#define DISABLE_JOYCON		//JoyConを無効化
//#define DISABLE_KEYBOARD		//キーボードを無効化	
//#define DISABLE_MOUSE			//マウスを無効化

#define	NUM_KEY_MAX			(256)	// キーの最大数

//===============================================
//	関数
//===============================================	
void Input_Initalize(HWND hWnd, HINSTANCE hInstance);
void Input_Update(HWND hWnd);
void Input_Finalize();

//-------------------------------------
//	デバイス情報
//-------------------------------------
#if !defined SYSTEM_H
LPDIRECT3DDEVICE9 System_GetDevice(void);	//デバイスの取得
#endif // !SYSTEM_H

//-------------------------------------
//	キーボード情報	DIK
//-------------------------------------

#if !defined DISABLE_KEYBOARD
bool Keyboard_IsPress(int nDIK);	//キーボードを押してる
bool Keyboard_IsTrigger(int nDIK);	//キーボードを押した
bool Keyboard_IsRelease(int nDIK);	//キーボードを放した
#endif

//-------------------------------------
//	マウス情報
//-------------------------------------
#if !defined DISABLE_MOUSE
bool Mouse_IsLeftDown();			//マウス左を押した
bool Mouse_IsRightDown();			//マウス右を押した
bool Mouse_IsCenterDown();			//マウスのセンター
float Mouse_IsAccelerationX();		//マウス加速度　X
float Mouse_IsAccelerationY();		//マウス加速度　Y
float Mouse_IsAccelerationZ();		//マウス加速度	Z(ホイール)
float Mouse_IsMouseX();				//マウスのX座標
float Mouse_IsMouseY();				//マウスのY座標
#endif

//-------------------------------------
//	ゲームパッド情報 (DS4)
//-------------------------------------
#if !defined DISABLE_GAMEPAD

#endif

#endif