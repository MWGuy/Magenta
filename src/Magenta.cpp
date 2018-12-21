#include "Magenta.h"
#include "Widget.h"

#ifdef _WIN32

#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static HRGN winRect;

enum WindowTransforming {
	Idle,
	SizingLeft,
	SizingLeftTop,
	SizingLeftBottom,
	SizingRight,
	SizingRightTop,
	SizingRightBottom,
	SizingTop,
	SizingBottom,
	Moving
};
static WindowTransforming winTransforming = Idle;
static BOOL mouseDown = false;
static unsigned int offsetX = 0;
static unsigned int offsetY = 0;

VOID adaptWindowRect(HWND hWnd) {
	RECT newRect;
	GetClientRect(hWnd, (LPRECT)&newRect);
	winRect = CreateRoundRectRgn(newRect.left, newRect.top, newRect.right - newRect.left,
		newRect.bottom - newRect.top, 12, 12);
	SetWindowRgn(hWnd, winRect, true);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("Magenta");

	RegisterClass(&wndClass);

	hWnd = CreateWindowEx(
		WS_EX_TRANSPARENT,
		TEXT("Magenta"),          // window class name
		TEXT("Magenta"),          // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	LONG lStyle = GetWindowLong(hWnd, GWL_STYLE);
	lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
	SetWindowLong(hWnd, GWL_STYLE, lStyle);

	adaptWindowRect(hWnd);

	ShowWindow(hWnd, iCmdShow);

	auto mwindow = new Magenta::Window(hWnd, "");

#define box1_id 11
	Magenta::Frame* frame = Magenta::createFrame(mwindow->layout().root(), box1_id);
	frame->height = 120;
	frame->relativeWidth = 50;
	frame->position = Magenta::BottomCenter;
	frame->y = -40;

	mwindow->layout().update();

	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	delete mwindow;

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOVING:
	case WM_SIZING:
	case WM_SIZE:
		adaptWindowRect(hWnd);
		break;
	case WM_LBUTTONDOWN:
		mouseDown = true;
		break;
	case WM_LBUTTONUP:
		mouseDown = false;
		break;
	case WM_MOUSEMOVE:

		if (mouseDown)
		{
			switch (winTransforming)
			{
			case Idle:
				break;
			case SizingLeft:
				
				break;
			case SizingLeftTop:
				
				break;
			case SizingLeftBottom:
				
				break;
			case SizingRight:

				break;
			case SizingRightTop:

				break;
			case SizingRightBottom:

				break;
			case SizingTop:

				break;
			case SizingBottom:

				break;
			case Moving:

				break;
			}
			return 0;
		}

		WORD posX, posY;
		posX = LOWORD(lParam);
		posY = HIWORD(lParam);

		offsetX = posX;
		offsetY = posY;

		RECT wndRect;
		GetClientRect(hWnd, (LPRECT)&wndRect);

#define BORDER_LEN 4

		if (posX < BORDER_LEN) {
			if (posY < BORDER_LEN) {
				SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
				winTransforming = SizingLeftTop;
			}
			else if (posY > wndRect.bottom - wndRect.top - BORDER_LEN * 12) {
				SetCursor(LoadCursor(NULL, IDC_SIZENESW));
				winTransforming = SizingLeftBottom;
			}
			else {
				SetCursor(LoadCursor(NULL, IDC_SIZEWE));
				winTransforming = SizingLeft;
			}
		}
		else if (posX > wndRect.right - wndRect.left - BORDER_LEN * 7) {
			if (posY < BORDER_LEN) {
				SetCursor(LoadCursor(NULL, IDC_SIZENESW));
				winTransforming = SizingRightTop;
			}
			else if (posY > wndRect.bottom - wndRect.top - BORDER_LEN * 12) {
				SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
				winTransforming = SizingRightBottom;
			}
			else {
				SetCursor(LoadCursor(NULL, IDC_SIZEWE));
				winTransforming = SizingRight;
			}
		}
		else if (posY < BORDER_LEN) {
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
			winTransforming = SizingTop;
		}
		else if (posY > wndRect.bottom - wndRect.top - BORDER_LEN * 12) {
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
			winTransforming = SizingBottom;
		}
		else {
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			winTransforming = Idle;
		}

		return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

#endif
