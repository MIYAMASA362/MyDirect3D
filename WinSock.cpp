//
//	WinSock.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/03
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include"common.h"
#include"System.h"

#include<stdio.h>
#include<io.h>
#include<Fcntl.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

#include"WinSock.h"
#include"resource1.h"

#pragma comment (lib,"Ws2_32.lib")

//===============================================
//	�}�N����`		define
//===============================================
#define WM_SOCKET WM_APP
#define ID_EDIT_FLAG		(0x8000)	//EDIT���Ɣ��ʂ���bit

#define ID_PORT_EDIT		(ID_EDIT_FLAG ^ 0x0001) //�|�[�g�ԍ�EDIT
#define ID_LOG_EDIT			(ID_EDIT_FLAG ^ 0x0002)	//���O�\��ID
#define ID_HOST_EDIT		(ID_EDIT_FLAG ^ 0x0004)	//�z�X�gID
#define ID_IPADDRESS_EDIT	(ID_EDIT_FLAG ^ 0x0008)	//IP�A�h���XID
#define ID_MESSAGE_EDIT		(ID_EDIT_FLAG ^ 0x0009)

#define ID_BUTTON_FLAG		(0x4000)	//BUTTON���Ɣ��ʂ���bit

#define ID_CONECT_BUTTON	(ID_BUTTON_FLAG ^ 0x0001)	//�ڑ��{�^��ID
#define ID_LEAVE_BUTTON		(ID_BUTTON_FLAG ^ 0x0002)	//�E�ރ{�^��ID
#define ID_CONSOLE_BUTTON	(ID_BUTTON_FLAG ^ 0x0003)
#define ID_MESSAGE_BUTTON	(ID_BUTTON_FLAG ^ 0x0004)

#define BROADCAST_ADDRESS ("255.255.255.255")			//�u���[�h�L���X�g�A�h���X

#define USER_NUM			(4)			//���[�U�[��
#define USER_NAME_LENGTH	(30)		//���[�U�[������
#define PORT_LENGTH			(30)		//Port����

//===============================================
//	�\����
//===============================================

//-------------------------------------
//	����M�f�[�^
//-------------------------------------
struct UDP_DATA
{
	char UserName[USER_NAME_LENGTH];
		
};

//-------------------------------------
//	�ڑ��҂̏��
//-------------------------------------
struct CLIENT_DATA
{
	char UserName[USER_NAME_LENGTH];
};

//===============================================
//	�O���[�o���ϐ�	global
//===============================================

//-------------------------------------
//	WinSock
//-------------------------------------
MSG g_WSMsg = {};

//---------------------------
//	��M���@Server
//---------------------------
SOCKET g_RecvSock = NULL;		//�\�P�b�g���
SOCKADDR_IN g_RecvAddr = {};	//�|�[�g���

//---------------------------
//	���M�� Client
//---------------------------
SOCKET g_CastSock = NULL;		//�\�P�b�g���
SOCKADDR_IN g_CastAddr = {};	//�|�[�g���

//---------------------------
//	Message
//---------------------------
char buf[2048];					//��M���b�Z�[�W

//-------------------------------------
//	API
//-------------------------------------
int hConsole = 0;	//�R���\�[�����
FILE* fp = NULL;

static HWND g_hWnd = {};
static HINSTANCE g_hInstance = {};

static HWND g_PortEditWnd = {};		//�|�[�g����
static HWND g_UserNameEditWnd = {};//���[�U�[������
static HWND g_MessageEditWnd = {};

static HWND g_ConectButton = {};	//�ڑ��E�ؒf�{�^��
static HWND g_MessageButton = {};	

//-------------------------------------
//	�f�[�^�ۑ�
//-------------------------------------
CLIENT_DATA Client[USER_NUM];		//�ڑ���

//===============================================
//	�֐�			function
//===============================================
LRESULT CALLBACK WinSockPoc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//-------------------------------------
//	�E�C���h�E����
//-------------------------------------
void WinSock_Window(HINSTANCE hInstance,HWND hParent)
{
	g_hInstance = hInstance;

	WNDCLASS WinSockWindow = {};
	WinSockWindow.lpfnWndProc = WinSockPoc;
	WinSockWindow.hInstance = hInstance;
	WinSockWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
	WinSockWindow.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	WinSockWindow.lpszClassName = "WinSock_Window";

	RegisterClass(&WinSockWindow);
	RECT Window_Rect;

	GetWindowRect(hParent, &Window_Rect);

	g_hWnd = CreateWindow(
		WinSockWindow.lpszClassName,
		NULL,
		WS_CHILD,	//�q�E�B���h�E
		0,
		0,
		Window_Rect.right - Window_Rect.left,
		Window_Rect.bottom - Window_Rect.top,
		hParent,	//�e
		(HMENU)"WinSock",
		hInstance,
		NULL
	);

	//���[�U�[������EDIT
	g_UserNameEditWnd = CreateWindow(
		TEXT("EDIT"),
		TEXT(""),
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		100, 10, 200, 20,
		g_hWnd,
		(HMENU)ID_IPADDRESS_EDIT,
		g_hInstance,
		NULL
	);

	//�|�[�g�ԍ�����EDIT
	g_PortEditWnd = CreateWindow(
		TEXT("EDIT"),
		TEXT(""),
		WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER,
		100, 40, 200, 20,
		g_hWnd,
		(HMENU)ID_PORT_EDIT,
		g_hInstance,
		NULL
	);

	//���b�Z�[�W����EDIT
	g_MessageEditWnd = CreateWindow(
		TEXT("EDIT"),
		TEXT(""),
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 100, 400, 20,
		g_hWnd,
		(HMENU)ID_MESSAGE_EDIT,
		g_hInstance,
		NULL
	);

	//���b�Z�[�W���M�{�^��
	g_MessageButton = CreateWindow(
		TEXT("BUTTON"),
		TEXT("���M"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		10, 130,
		100, 20,
		g_hWnd,
		(HMENU)ID_MESSAGE_BUTTON,
		g_hInstance,
		NULL
	);

	//�ڑ��{�^��
	g_ConectButton = CreateWindow(
		TEXT("BUTTON"),
		TEXT("�ڑ�"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		10,70,
		100,20,
		g_hWnd,
		(HMENU)ID_CONECT_BUTTON,
		g_hInstance,
		NULL
	);

	//�R���\�[���\���{�^��
	CreateWindow(
		TEXT("BUTTON"),
		TEXT("�R���\�[��"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		320, 10,
		100, 20,
		g_hWnd,
		(HMENU)ID_CONSOLE_BUTTON,
		g_hInstance,
		NULL
	);

	if (g_hWnd == NULL)
	{
		MessageBox(NULL, "WinSockWindow�̃n���h�������Ɏ��s���܂����B", "�G���[", MB_OK);
		return;
	}

	ShowWindow(g_hWnd,SW_HIDE);

	return;
}

//-------------------------------------
//	�\���E��\���̕ύX
//-------------------------------------
void WindSock_SetWindow(BOOL Show)
{
	//True �\��
	if(Show)
	{
		ShowWindow(g_hWnd, SW_SHOW);
		UpdateWindow(g_hWnd);
	}
	//False ��\��
	else
	{
		ShowWindow(g_hWnd,SW_HIDE);
	}
	return;
}

//=========================================================
//	WinSock �֌W�̊֐�
//=========================================================

//-------------------------------------
//	������
//-------------------------------------
void WinSock_Initialize()
{
	//WinSock2������
	WORD wVersionRequored = MAKEWORD(2,0);
	WSADATA wsaData;
	INT result =  WSAStartup(wVersionRequored,&wsaData);

	//�G���[����
	if(result != 0)
	{
		switch (result)
		{
		case WSASYSNOTREADY:
			MessageBox(NULL,"�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��Ȃ��B","WinSock",MB_OK);
			break;
		case WSAVERNOTSUPPORTED:
			MessageBox(NULL,"�v�����ꂽWinSock�̃o�[�W�������T�|�[�g����Ă��Ȃ��B","WinSock",MB_OK);
			break;
		case WSAEINPROGRESS:
			MessageBox(NULL,"�u���b�L���O����̎��s���ł��邩,\n�T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă��܂��B","WinSock",MB_OK);
			break;
		case WSAEPROCLIM:
			MessageBox(NULL, "WinSock�������ł���ő�v���Z�X���ɒB���܂����B", "WinSock", MB_OK);
			break;
		default:
			MessageBox(NULL,"�Ȃ�炩�̃G���[���������܂����B","WinSock",MB_OK);
			break;
		}
	}

	//�o�[�W��������
	if(wsaData.wVersion != wVersionRequored)
	{
		MessageBox(0,"WinSock2�̏������Ɏ��s���܂����B","WinSock",MB_OK);
		return;
	}

	return;
}

//-------------------------------------
//	���[�U�[���擾
//-------------------------------------
TCHAR* UserNameEditInput()
{
	TCHAR UserName[USER_NAME_LENGTH];

	GetWindowText(g_UserNameEditWnd,UserName,sizeof(UserName));

	return &UserName[0];
}


//-------------------------------------
//	�|�[�g�ԍ����͎擾
//-------------------------------------
TCHAR* PortEditInput()
{
	TCHAR InputPort[PORT_LENGTH];		//���̓|�[�g�ԍ�

	//	�|�[�g�ԍ��̎擾
	//----------------------------------
	GetWindowText(g_PortEditWnd, InputPort, sizeof(InputPort)); //���͒l�擾

	if (InputPort == NULL) 
	{
		MessageBox(NULL,"�����ȃ|�[�g�ԍ��ł��B","WinSock",MB_OK);
		return NULL;
	}

	return &InputPort[0];
}

//-------------------------------------
//	������
//-------------------------------------
void WinSock_Close()
{
	closesocket(g_CastSock);
	closesocket(g_RecvSock);

	return;
}

//=========================================================
//	Server ��M���̊֐�
//=========================================================

//-------------------------------------
//	��M�J�n
//-------------------------------------
int Server_Begin()
{
	int Port;					//�擾�|�[�g�ԍ�
	Port = atoi(PortEditInput());

	if (Port == NULL)return 1;
	
	printf("WinSock->Server = Port[%d]\n", Port);

	memset(&g_RecvAddr, 0, sizeof(g_RecvAddr));
	g_RecvAddr.sin_family = AF_INET;
	g_RecvAddr.sin_port = htons(Port);
	g_RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	memset(&g_RecvSock, 0, sizeof(g_RecvSock));
	g_RecvSock = socket(AF_INET, SOCK_DGRAM, 0);

	bind(g_RecvSock, (struct sockaddr*)&g_RecvAddr, sizeof(g_RecvAddr));

	return 0;
}

//-------------------------------------
//	�f�[�^�̎�M
//-------------------------------------
TCHAR* WinSock_Receiver()
{
	if(recvfrom(g_RecvSock,buf,sizeof(buf),0,NULL,NULL) == -1)
	{
		return NULL;
	}
	printf("%s\n",buf);

	return &buf[0];
}

//-------------------------------------
//	��M�I��
//-------------------------------------
void Server_End()
{
	closesocket(g_RecvSock);
	g_RecvSock = NULL;
}

//=========================================================
//	Client	���M���̊֐�
//=========================================================

//-------------------------------------
//	�ڑ��J�n
//-------------------------------------
int Client_Begin()
{
	int Port;					//�擾�|�[�g�ԍ�
	int OnBroad = 1;

	//	�|�[�g�ԍ��擾
	//-------------------------------------
	Port = atoi(PortEditInput());

	if (Port == NULL)return 1;

	printf("WinSock->Client = Port[%d]\n", Port);

	char toSendText[300] = { "\0" };

	memset(&g_CastAddr, 0, sizeof(g_CastAddr));

	g_CastAddr.sin_family = AF_INET;
	g_CastAddr.sin_port = htons(Port);
	g_CastAddr.sin_addr.s_addr = inet_addr(BROADCAST_ADDRESS);

	g_CastSock = socket(AF_INET, SOCK_DGRAM, 0);

	//�u���[�h�L���X�g ON
	setsockopt(g_CastSock, SOL_SOCKET, SO_BROADCAST, (char*)&OnBroad, sizeof(OnBroad));

	char JoinMessage[100];

	strcpy(&JoinMessage[0], "\0");
	strcat(&JoinMessage[0], "Join:");
	strcat(&JoinMessage[0], UserNameEditInput());
	sendto(g_CastSock, JoinMessage, (int)strlen(JoinMessage) + 1, 0, (struct sockaddr*)&g_CastAddr, sizeof(g_CastAddr));

	return 0;
}

//-------------------------------------
//	�f�[�^�̑��M
//-------------------------------------
void WinSock_Send(char* SendMsg)
{
	
}

//-------------------------------------
//	�ڑ��I��
//-------------------------------------
void Client_End()
{
	char LeaveMessage[100];

	strcpy(&LeaveMessage[0],"\0");
	strcat(&LeaveMessage[0],"Leave:");
	strcat(&LeaveMessage[0],UserNameEditInput());
	sendto(g_CastSock, LeaveMessage, (int)strlen(LeaveMessage) + 1, 0, (struct sockaddr*)&g_CastAddr, sizeof(g_CastAddr));

	closesocket(g_CastSock);
}


//=========================================================
//	�R�[���o�b�N�֐�
//=========================================================

//-------------------------------------
//	�R�[���o�b�N�֐�
//-------------------------------------
LRESULT CALLBACK WinSockPoc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;				//�f�o�C�X�R���e�L�X�g
	PAINTSTRUCT stPaint;	//�`��p

	switch (uMsg)
	{
	case WM_CREATE:
		WinSock_Initialize();
		break;

	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
		{
			SendMessage(hWnd,WM_CLOSE,0,0);
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_COMMAND:

		//���b�Z�[�WID
		switch(LOWORD(wParam))
		{

		//===================================
		//	�ڑ�
		//===================================
		case ID_CONECT_BUTTON:

			// ����M�J�n
			//-----------------------------------
			if(Server_Begin()|| Client_Begin())
			{
				Server_End();
				Client_End();
				break;
			}

			//	�ڑ��{�^���𗣒E�{�^���ɕύX
			//----------------------------------
			if (g_ConectButton != NULL)
			{
				DestroyWindow(g_ConectButton);
			}

			g_ConectButton = CreateWindow(
				TEXT("BUTTON"),
				TEXT("���E"),
				WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
				120, 70,
				100, 20,
				g_hWnd,
				(HMENU)ID_LEAVE_BUTTON,
				g_hInstance,
				NULL
			);

			printf("WinSock:Conect\n");

			break;

		//===================================
		//	���E
		//===================================
		case ID_LEAVE_BUTTON:

			//	����M�I��
			//----------------------------------
			Server_End();
			Client_End();

			DestroyWindow(g_ConectButton);
			g_ConectButton = CreateWindow(
				TEXT("BUTTON"),
				TEXT("�ڑ�"),
				WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
				10, 70,
				100, 20,
				g_hWnd,
				(HMENU)ID_CONECT_BUTTON,
				g_hInstance,
				NULL
			);

			printf("WinSock:Leave\n");

			break;

		case ID_CONSOLE_BUTTON:

			//	�R���\�[���E�B���h�E
			//----------------------------------
			FreeConsole();
			AllocConsole();
			freopen_s(&fp, "CONOUT$", "w", stdout);
			freopen_s(&fp, "CONIN$", "r", stdin);
			
			break;

		case ID_MESSAGE_BUTTON:

			char Message[300];

			TCHAR InputMessage[30];

			GetWindowText(g_MessageEditWnd, InputMessage, sizeof(InputMessage)); //���͒l�擾

			strcpy(&Message[0], "\0");
			strcat(&Message[0], UserNameEditInput());
			strcat(&Message[0], ":");
			strcat(&Message[0],&InputMessage[0]);
			sendto(g_CastSock, Message, (int)strlen(Message) + 1, 0, (struct sockaddr*)&g_CastAddr, sizeof(g_CastAddr));

			break;

		default:
			break;
		}
		break;

	case WM_SOCKET:

		switch (LOWORD(lParam))
		{
		case FD_READ:
			MessageBox(NULL,"���b�Z�[�W�͂���","WinSock",MB_OK);

			break;
		default:
			break;
		}
		
	case WM_PAINT:

		//�����`��
		hdc = BeginPaint(hWnd,&stPaint);
		
		TextOut(hdc, 10, 10, TEXT("���[�U�[��"), lstrlen(TEXT("���[�U�[��")));
		TextOut(hdc, 10, 40, TEXT("�|�[�g�ԍ�"), lstrlen(TEXT("�|�[�g�ԍ�")));

		EndPaint(hWnd, &stPaint);

		break;

	case WM_DESTROY:
		WinSock_Close();
		WSACleanup();
		FreeConsole();
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

