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
//	�}�N����`
//===============================================
//#define DISABLE_GAMEPAD		//�Q�[���p�b�h�𖳌���
//#define DISABLE_DS4			//DualShock4�𖳌���
//#define DISABLE_JOYCON		//JoyCon�𖳌���
//#define DISABLE_KEYBOARD		//�L�[�{�[�h�𖳌���	
//#define DISABLE_MOUSE			//�}�E�X�𖳌���

#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔

//===============================================
//	�֐�
//===============================================	
void Input_Initalize(HWND hWnd, HINSTANCE hInstance);
void Input_Update(HWND hWnd);
void Input_Finalize();

//-------------------------------------
//	�f�o�C�X���
//-------------------------------------
#if !defined SYSTEM_H
LPDIRECT3DDEVICE9 System_GetDevice(void);	//�f�o�C�X�̎擾
#endif // !SYSTEM_H

//-------------------------------------
//	�L�[�{�[�h���	DIK
//-------------------------------------

#if !defined DISABLE_KEYBOARD
bool Keyboard_IsPress(int nDIK);	//�L�[�{�[�h�������Ă�
bool Keyboard_IsTrigger(int nDIK);	//�L�[�{�[�h��������
bool Keyboard_IsRelease(int nDIK);	//�L�[�{�[�h�������
#endif

//-------------------------------------
//	�}�E�X���
//-------------------------------------
#if !defined DISABLE_MOUSE
bool Mouse_IsLeftDown();			//�}�E�X����������
bool Mouse_IsRightDown();			//�}�E�X�E��������
bool Mouse_IsCenterDown();			//�}�E�X�̃Z���^�[
float Mouse_IsAccelerationX();		//�}�E�X�����x�@X
float Mouse_IsAccelerationY();		//�}�E�X�����x�@Y
float Mouse_IsAccelerationZ();		//�}�E�X�����x	Z(�z�C�[��)
float Mouse_IsMouseX();				//�}�E�X��X���W
float Mouse_IsMouseY();				//�}�E�X��Y���W
#endif

//-------------------------------------
//	�Q�[���p�b�h��� (DS4)
//-------------------------------------
#if !defined DISABLE_GAMEPAD

#endif

#endif