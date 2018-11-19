//
//	WinSock.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/03
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
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
//	マクロ定義		define
//===============================================
#define WM_SOCKET WM_APP
#define ID_EDIT_FLAG		(0x8000)	//EDITだと判別するbit

#define ID_PORT_EDIT		(ID_EDIT_FLAG ^ 0x0001) //ポート番号EDIT
#define ID_LOG_EDIT			(ID_EDIT_FLAG ^ 0x0002)	//ログ表示ID
#define ID_HOST_EDIT		(ID_EDIT_FLAG ^ 0x0004)	//ホストID
#define ID_IPADDRESS_EDIT	(ID_EDIT_FLAG ^ 0x0008)	//IPアドレスID
#define ID_MESSAGE_EDIT		(ID_EDIT_FLAG ^ 0x0009)

#define ID_BUTTON_FLAG		(0x4000)	//BUTTONだと判別するbit

#define ID_CONECT_BUTTON	(ID_BUTTON_FLAG ^ 0x0001)	//接続ボタンID
#define ID_LEAVE_BUTTON		(ID_BUTTON_FLAG ^ 0x0002)	//脱退ボタンID
#define ID_CONSOLE_BUTTON	(ID_BUTTON_FLAG ^ 0x0003)
#define ID_MESSAGE_BUTTON	(ID_BUTTON_FLAG ^ 0x0004)

#define BROADCAST_ADDRESS ("255.255.255.255")			//ブロードキャストアドレス

#define USER_NUM			(4)			//ユーザー数
#define USER_NAME_LENGTH	(30)		//ユーザー名長さ
#define PORT_LENGTH			(30)		//Port長さ

//===============================================
//	構造体
//===============================================

//-------------------------------------
//	送受信データ
//-------------------------------------
struct UDP_DATA
{
	char UserName[USER_NAME_LENGTH];
		
};

//-------------------------------------
//	接続者の情報
//-------------------------------------
struct CLIENT_DATA
{
	char UserName[USER_NAME_LENGTH];
};

//===============================================
//	グローバル変数	global
//===============================================

//-------------------------------------
//	WinSock
//-------------------------------------
MSG g_WSMsg = {};

//---------------------------
//	受信側　Server
//---------------------------
SOCKET g_RecvSock = NULL;		//ソケット情報
SOCKADDR_IN g_RecvAddr = {};	//ポート情報

//---------------------------
//	送信側 Client
//---------------------------
SOCKET g_CastSock = NULL;		//ソケット情報
SOCKADDR_IN g_CastAddr = {};	//ポート情報

//---------------------------
//	Message
//---------------------------
char buf[2048];					//受信メッセージ

//-------------------------------------
//	API
//-------------------------------------
int hConsole = 0;	//コンソール画面
FILE* fp = NULL;

static HWND g_hWnd = {};
static HINSTANCE g_hInstance = {};

static HWND g_PortEditWnd = {};		//ポート入力
static HWND g_UserNameEditWnd = {};//ユーザー名入力
static HWND g_MessageEditWnd = {};

static HWND g_ConectButton = {};	//接続・切断ボタン
static HWND g_MessageButton = {};	

//-------------------------------------
//	データ保存
//-------------------------------------
CLIENT_DATA Client[USER_NUM];		//接続者

//===============================================
//	関数			function
//===============================================
LRESULT CALLBACK WinSockPoc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//-------------------------------------
//	ウインドウ生成
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
		WS_CHILD,	//子ウィンドウ
		0,
		0,
		Window_Rect.right - Window_Rect.left,
		Window_Rect.bottom - Window_Rect.top,
		hParent,	//親
		(HMENU)"WinSock",
		hInstance,
		NULL
	);

	//ユーザー名入力EDIT
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

	//ポート番号入力EDIT
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

	//メッセージ入力EDIT
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

	//メッセージ送信ボタン
	g_MessageButton = CreateWindow(
		TEXT("BUTTON"),
		TEXT("送信"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		10, 130,
		100, 20,
		g_hWnd,
		(HMENU)ID_MESSAGE_BUTTON,
		g_hInstance,
		NULL
	);

	//接続ボタン
	g_ConectButton = CreateWindow(
		TEXT("BUTTON"),
		TEXT("接続"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		10,70,
		100,20,
		g_hWnd,
		(HMENU)ID_CONECT_BUTTON,
		g_hInstance,
		NULL
	);

	//コンソール表示ボタン
	CreateWindow(
		TEXT("BUTTON"),
		TEXT("コンソール"),
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
		MessageBox(NULL, "WinSockWindowのハンドル生成に失敗しました。", "エラー", MB_OK);
		return;
	}

	ShowWindow(g_hWnd,SW_HIDE);

	return;
}

//-------------------------------------
//	表示・非表示の変更
//-------------------------------------
void WindSock_SetWindow(BOOL Show)
{
	//True 表示
	if(Show)
	{
		ShowWindow(g_hWnd, SW_SHOW);
		UpdateWindow(g_hWnd);
	}
	//False 非表示
	else
	{
		ShowWindow(g_hWnd,SW_HIDE);
	}
	return;
}

//=========================================================
//	WinSock 関係の関数
//=========================================================

//-------------------------------------
//	初期化
//-------------------------------------
void WinSock_Initialize()
{
	//WinSock2初期化
	WORD wVersionRequored = MAKEWORD(2,0);
	WSADATA wsaData;
	INT result =  WSAStartup(wVersionRequored,&wsaData);

	//エラー処理
	if(result != 0)
	{
		switch (result)
		{
		case WSASYSNOTREADY:
			MessageBox(NULL,"ネットワークサブシステムがネットワークへの接続を準備できていない。","WinSock",MB_OK);
			break;
		case WSAVERNOTSUPPORTED:
			MessageBox(NULL,"要求されたWinSockのバージョンがサポートされていない。","WinSock",MB_OK);
			break;
		case WSAEINPROGRESS:
			MessageBox(NULL,"ブロッキング操作の実行中であるか,\nサービスプロバイダがコールバック関数を処理しています。","WinSock",MB_OK);
			break;
		case WSAEPROCLIM:
			MessageBox(NULL, "WinSockが処理できる最大プロセス数に達しました。", "WinSock", MB_OK);
			break;
		default:
			MessageBox(NULL,"なんらかのエラーが発生しました。","WinSock",MB_OK);
			break;
		}
	}

	//バージョン錯誤
	if(wsaData.wVersion != wVersionRequored)
	{
		MessageBox(0,"WinSock2の初期化に失敗しました。","WinSock",MB_OK);
		return;
	}

	return;
}

//-------------------------------------
//	ユーザー名取得
//-------------------------------------
TCHAR* UserNameEditInput()
{
	TCHAR UserName[USER_NAME_LENGTH];

	GetWindowText(g_UserNameEditWnd,UserName,sizeof(UserName));

	return &UserName[0];
}


//-------------------------------------
//	ポート番号入力取得
//-------------------------------------
TCHAR* PortEditInput()
{
	TCHAR InputPort[PORT_LENGTH];		//入力ポート番号

	//	ポート番号の取得
	//----------------------------------
	GetWindowText(g_PortEditWnd, InputPort, sizeof(InputPort)); //入力値取得

	if (InputPort == NULL) 
	{
		MessageBox(NULL,"無効なポート番号です。","WinSock",MB_OK);
		return NULL;
	}

	return &InputPort[0];
}

//-------------------------------------
//	閉鎖処理
//-------------------------------------
void WinSock_Close()
{
	closesocket(g_CastSock);
	closesocket(g_RecvSock);

	return;
}

//=========================================================
//	Server 受信側の関数
//=========================================================

//-------------------------------------
//	受信開始
//-------------------------------------
int Server_Begin()
{
	int Port;					//取得ポート番号
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
//	データの受信
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
//	受信終了
//-------------------------------------
void Server_End()
{
	closesocket(g_RecvSock);
	g_RecvSock = NULL;
}

//=========================================================
//	Client	送信側の関数
//=========================================================

//-------------------------------------
//	接続開始
//-------------------------------------
int Client_Begin()
{
	int Port;					//取得ポート番号
	int OnBroad = 1;

	//	ポート番号取得
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

	//ブロードキャスト ON
	setsockopt(g_CastSock, SOL_SOCKET, SO_BROADCAST, (char*)&OnBroad, sizeof(OnBroad));

	char JoinMessage[100];

	strcpy(&JoinMessage[0], "\0");
	strcat(&JoinMessage[0], "Join:");
	strcat(&JoinMessage[0], UserNameEditInput());
	sendto(g_CastSock, JoinMessage, (int)strlen(JoinMessage) + 1, 0, (struct sockaddr*)&g_CastAddr, sizeof(g_CastAddr));

	return 0;
}

//-------------------------------------
//	データの送信
//-------------------------------------
void WinSock_Send(char* SendMsg)
{
	
}

//-------------------------------------
//	接続終了
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
//	コールバック関数
//=========================================================

//-------------------------------------
//	コールバック関数
//-------------------------------------
LRESULT CALLBACK WinSockPoc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;				//デバイスコンテキスト
	PAINTSTRUCT stPaint;	//描画用

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

		//メッセージID
		switch(LOWORD(wParam))
		{

		//===================================
		//	接続
		//===================================
		case ID_CONECT_BUTTON:

			// 送受信開始
			//-----------------------------------
			if(Server_Begin()|| Client_Begin())
			{
				Server_End();
				Client_End();
				break;
			}

			//	接続ボタンを離脱ボタンに変更
			//----------------------------------
			if (g_ConectButton != NULL)
			{
				DestroyWindow(g_ConectButton);
			}

			g_ConectButton = CreateWindow(
				TEXT("BUTTON"),
				TEXT("離脱"),
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
		//	離脱
		//===================================
		case ID_LEAVE_BUTTON:

			//	送受信終了
			//----------------------------------
			Server_End();
			Client_End();

			DestroyWindow(g_ConectButton);
			g_ConectButton = CreateWindow(
				TEXT("BUTTON"),
				TEXT("接続"),
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

			//	コンソールウィンドウ
			//----------------------------------
			FreeConsole();
			AllocConsole();
			freopen_s(&fp, "CONOUT$", "w", stdout);
			freopen_s(&fp, "CONIN$", "r", stdin);
			
			break;

		case ID_MESSAGE_BUTTON:

			char Message[300];

			TCHAR InputMessage[30];

			GetWindowText(g_MessageEditWnd, InputMessage, sizeof(InputMessage)); //入力値取得

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
			MessageBox(NULL,"メッセージ届いた","WinSock",MB_OK);

			break;
		default:
			break;
		}
		
	case WM_PAINT:

		//文字描画
		hdc = BeginPaint(hWnd,&stPaint);
		
		TextOut(hdc, 10, 10, TEXT("ユーザー名"), lstrlen(TEXT("ユーザー名")));
		TextOut(hdc, 10, 40, TEXT("ポート番号"), lstrlen(TEXT("ポート番号")));

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

