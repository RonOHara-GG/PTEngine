// PTTest.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "PTTest.h"

#define MAX_LOADSTRING 100

extern void InitGame(HWND hWndTop, HWND hWndBottom);
extern void ShutdownGame();
extern void DoFrame();

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND hMainWnd;
HWND hTopWindow;
HWND hBottomWindow;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PTTEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PTTEST));

    InitGame(hTopWindow, hBottomWindow);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

        DoFrame();
	}

    ShutdownGame();

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PTTEST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

   hInst = hInstance; // Store instance handle in our global variable

   int renderHeight = 480;
   int renderWidth = (int)((16.0f / 9.0f) * (float)renderHeight);

   int screenX = GetSystemMetrics(SM_CXSCREEN);

   int width = renderWidth + 20;
   int xCtr = (screenX / 2) - (width / 2);

   hMainWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, xCtr, 0, width, (renderHeight * 2) + 45, NULL, NULL, hInstance, NULL);

   hTopWindow = CreateWindow(szWindowClass, szTitle, WS_CHILD | WS_BORDER, 2, 2, renderWidth, renderHeight, hMainWnd, NULL, hInstance, NULL);
   hBottomWindow = CreateWindow(szWindowClass, szTitle, WS_CHILD | WS_BORDER, 2, 4 + renderHeight, renderWidth, renderHeight, hMainWnd, NULL, hInstance, NULL);

   if (!hMainWnd)
   {
      return FALSE;
   }

   ShowWindow(hMainWnd, nCmdShow);
   ShowWindow(hTopWindow, nCmdShow);
   ShowWindow(hBottomWindow, nCmdShow);
   UpdateWindow(hMainWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

