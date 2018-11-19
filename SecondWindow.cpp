//
//	SecondWindow.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/24
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include<stdio.h>
#include<io.h>
#include<Fcntl.h>
#include<Windows.h>
#include<d3dx9.h>


#include"common.h"
#include"System.h"

#include"resource1.h"
#include"WinSock.h"

//Class

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================
HWND g_hWnd = {};
HINSTANCE g_hInstance = {};

//===============================================
//	�֐�			function
//===============================================
LRESULT CALLBACK SecondWndPoc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//-------------------------------------
//	������
//-------------------------------------
void SecondWindow_Create(HINSTANCE hInstance,int nCmdShow)
{
	WNDCLASS SecondWindow = {};
	SecondWindow.lpfnWndProc = SecondWndPoc;
	SecondWindow.hInstance = hInstance;
	SecondWindow.hCursor = LoadCursor(NULL,IDC_ARROW);
	SecondWindow.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	SecondWindow.lpszClassName = "Second_Window";
	SecondWindow.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);	//���j���[�o�[

	RegisterClass(&SecondWindow);

	RECT Window_Rect = {0,0,500,680};
	DWORD WindowStyle = (WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN));

	AdjustWindowRect(&Window_Rect,WindowStyle,FALSE);

	int WinWidth = Window_Rect.right - Window_Rect.left;
	int WinHeight = Window_Rect.bottom - Window_Rect.top;

	float WinPosX = max(200 + (GetSystemMetrics(SM_CXSCREEN) - WinWidth) * 0.5f,0);
	float WinPosY = max((GetSystemMetrics(SM_CYSCREEN) - WinHeight) * 0.5f,0);

	g_hWnd = CreateWindow(
		SecondWindow.lpszClassName,
		"SECOND_WINDOW",
		WindowStyle,
		WinPosX,WinPosY,
		WinWidth,WinHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (g_hWnd == NULL) return;
	

	ShowWindow(g_hWnd,nCmdShow);
	UpdateWindow(g_hWnd);

	WinSock_Window(g_hInstance, g_hWnd);


	//DirectX
	LPDIRECT3D9 pd3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (pd3d9 == NULL) 
	{
		MessageBox(g_hWnd,"�G���[","SecondWindow�̃f�o�C�X�擾�Ɏ��s���܂����B",MB_OK);
		return;
	}

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.BackBufferWidth = Window_Rect.right;
	d3dpp.BackBufferHeight = 200;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	LPDIRECT3DDEVICE9 Device = System_GetDevice();

	HRESULT hr = pd3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &Device);

	if(FAILED(hr))
	{
		MessageBox(g_hWnd,"�f�o�C�X�̎擾�Ɏ��s���܂����B","Second_Window:Error",MB_OK);
		DestroyWindow(g_hWnd);
		return;
	}

	MSG Msg = {};

	//------------------------------------
	//	���C�����[�v
	//------------------------------------
	do
	{
		if(PeekMessage(&Msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{

		}
	} while(Msg.wParam);

	return;
}


//-------------------------------------
//	�v���V�[�W���[����
//-------------------------------------
LRESULT CALLBACK SecondWndPoc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;

	case WM_DESTROY:
		
		//WM_QUIT�@�Ƃ������b�Z�[�W�𑗂�
		//PostQuitMessage(0);
		return 0;

	case WM_CREATE:

		return 0;
	case WM_COMMAND:

		//���b�Z�[�WID��
		switch (LOWORD(wParam))
		{
		case 0:
			CreateWindow(
				"BUTTON",
				TEXT("button"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100, 0, 100, 150,
				g_hWnd,
				NULL,
				g_hInstance,
				NULL
			);
			break;

		//Editer(Main)
		case ID_EDITER:
			WindSock_SetWindow(FALSE);
			break;
		//WinSock�E�B���h�E
		case ID_WINSOCK:
			WindSock_SetWindow(TRUE);
			break;

		default:
			break;
		}


		return 0;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

