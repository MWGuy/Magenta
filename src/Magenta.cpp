#include "Magenta.h"
#include "Widget.h"

#include "forms/AppWindowF.h"

#ifdef _WIN32

#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static HRGN winRect;

static Magenta::Window* mwindow = 0;
static WindowTransform winTransforming = Idle;
static BOOL mouseDown = false;
static unsigned int offsetX = 0;
static unsigned int offsetY = 0;
static unsigned int initialX = 0;
static unsigned int initialY = 0;
static unsigned int initialWidth = 0;
static unsigned int initialHeight = 0;

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

	SetTimer(hWnd, 1, 1, (TIMERPROC)&WndProc);

	ShowWindow(hWnd, iCmdShow);

	mwindow = new Magenta::Window(hWnd, MagentaForm::AppWindowF);
	mwindow->setTransformable(&winTransforming);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	KillTimer(hWnd, 1);
	delete mwindow;

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}

VOID updateContext(HDC hdc);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		updateContext(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOVING:
	case WM_SIZING:
	case WM_SIZE:
		adaptWindowRect(hWnd);
		break;
	case WM_LBUTTONDOWN:
		mouseDown = true;
		mwindow->layout().executeOnMouseDown();
		break;
	case WM_RBUTTONDOWN:
		mouseDown = true;
		mwindow->layout().executeOnMouseDown();
		break;
	case WM_LBUTTONUP:
		mouseDown = false;
		mwindow->layout().executeOnMouseUp();
		break;
	case WM_RBUTTONUP:
		mouseDown = false;
		mwindow->layout().executeOnMouseRightButtonUp();
		break;
	case WM_TIMER:

		if (mouseDown)
		{
			POINT p;
			GetCursorPos(&p);
			RECT rect;
			GetWindowRect(hWnd, &rect);

			unsigned long posX = p.x - offsetX;
			unsigned long posY = p.y - offsetY;
			unsigned long width = 0;
			unsigned long height = 0;

			switch (winTransforming)
			{
			case Idle:
				break;
			case SizingLeft:
				width = initialWidth + initialX - posX;
				if (width < window_min_width)
					width = window_min_width;
				MoveWindow(hWnd, posX, initialY, width, initialHeight, true);
				break;
			case SizingLeftTop:
				width = initialWidth + initialX - posX;
				if (width < window_min_width)
					width = window_min_width;
				height = initialHeight + initialY - posY;
				if (height < window_min_height)
					height = window_min_height;
				MoveWindow(hWnd, posX, posY, width, height, true);
				break;
			case SizingLeftBottom:
				width = initialWidth + initialX - posX;
				if (width < window_min_width)
					width = window_min_width;
				height = initialHeight - initialY + posY;
				if (height < window_min_height)
					height = window_min_height;
				MoveWindow(hWnd, posX, initialY, width, height, true);
				break;
			case SizingRight:
				width = initialWidth - initialX + posX;
				if (width < window_min_width)
					width = window_min_width;
				MoveWindow(hWnd, initialX, initialY, width, initialHeight, true);
				break;
			case SizingRightTop:
				width = initialWidth - initialX + posX;
				if (width < window_min_width)
					width = window_min_width;
				height = initialHeight + initialY - posY;
				if (height < window_min_height)
					height = window_min_height;
				MoveWindow(hWnd, initialX, posY, width, height, true);
				break;
			case SizingRightBottom:
				width = initialWidth - initialX + posX;
				if (width < window_min_width)
					width = window_min_width;
				height = initialHeight - initialY + posY;
				if (height < window_min_height)
					height = window_min_height;
				MoveWindow(hWnd, initialX, initialY, width, height, true);
				break;
			case SizingTop:
				height = initialHeight + initialY - posY;
				if (height < window_min_height)
					height = window_min_height;
				MoveWindow(hWnd, initialX, posY, initialWidth, height, true);
				break;
			case SizingBottom:
				height = initialHeight - initialY + posY;
				if (height < window_min_height)
					height = window_min_height;
				MoveWindow(hWnd, initialX, initialY, initialWidth, height, true);
				break;
			case Moving:
				MoveWindow(hWnd, posX, posY, initialWidth, initialHeight, true);
				break;
			}
			adaptWindowRect(hWnd);
		}
		break;
	case WM_MOUSEMOVE:
		mwindow->layout().executeOnMouseMove();
		if (mouseDown)
			return 0;

		WORD posX, posY;
		posX = LOWORD(lParam);
		posY = HIWORD(lParam);

		offsetX = posX;
		offsetY = posY;

		RECT wndRect;
		GetWindowRect(hWnd, (LPRECT)&wndRect);

		initialX = wndRect.left;
		initialY = wndRect.top;
		initialWidth = wndRect.right - wndRect.left;
		initialHeight = wndRect.bottom - wndRect.top;

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

VOID updateContext(HDC hdc) {
	if (mwindow != 0) {
		mwindow->layout().update();
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(mwindow->layout().view, 0, 0);
	}
}

#endif
