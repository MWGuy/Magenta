#include "Magenta.h"
#include "Widget.h"
#include "SFML/Graphics.hpp"

#include "forms/AppWindowF.h"

#ifdef _WIN32

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK InnProc(HWND, UINT, WPARAM, LPARAM);

static HRGN winRect = CreateRoundRectRgn(0, 0, 0, 0, 0, 0);

static HWND hInner = 0;

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
	if (hInner == 0)
		return;

	RECT mwRect;
	GetWindowRect(hWnd, (LPRECT)&mwRect);

	RECT newRect;
	GetClientRect(hInner, (LPRECT)&newRect);
	if (mwindow == 0  || !mwindow->isMaximized())
	{
		MoveWindow(hInner, mwRect.left + 4, mwRect.top + 4, mwRect.right - mwRect.left - 8,
			mwRect.bottom - mwRect.top - 8, true);

		DeleteObject(winRect);
		winRect = CreateRoundRectRgn(newRect.left, newRect.top, newRect.right - newRect.left,
			newRect.bottom - newRect.top, 12, 12);
		SetWindowRgn(hInner, winRect, true);
	}
	else {
		SetWindowRgn(hInner, NULL, true);
	}
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	WNDCLASS            innClass;
	ULONG_PTR           gdiplusToken;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("ma_main_window");
	RegisterClass(&wndClass);

	innClass.style = CS_HREDRAW | CS_VREDRAW;
	innClass.lpfnWndProc = InnProc;
	innClass.cbClsExtra = 0;
	innClass.cbWndExtra = 0;
	innClass.hInstance = hInstance;
	innClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	innClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	innClass.hbrBackground = (HBRUSH)(WHITE_BRUSH);
	innClass.lpszMenuName = NULL;
	innClass.lpszClassName = TEXT("ma_inner");
	RegisterClass(&innClass);

	hWnd = CreateWindowEx(
		WS_EX_TRANSPARENT,
		TEXT("ma_main_window"),   // window class name
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

	// Apply transparent style
	MoveWindow(hWnd, 200, 200, 800, 580, false);

	SetTimer(hWnd, 1, 1, (TIMERPROC)&WndProc);

	hInner = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("ma_inner"), NULL, 0, 0, 0, 0, 0, hWnd, NULL, hInstance, NULL);

	lStyle = GetWindowLong(hInner, GWL_STYLE);
	lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
	SetWindowLong(hInner, GWL_STYLE, lStyle);

	// Hide inner
	MoveWindow(hInner, 10000, 0, 0, 0, false);

	mwindow = new Magenta::Window(hInner, hWnd, MagentaForm::AppWindowF);
	mwindow->setTransformable(&winTransforming);

	ShowWindow(hWnd, iCmdShow);

	RECT workArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
	MoveWindow(hWnd, workArea.right/2 - 400, workArea.bottom / 2 - 290, 800, 580, true);

	adaptWindowRect(hWnd);

	ShowWindow(hInner, SW_SHOWNORMAL);

	msg.message = ~WM_QUIT;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	KillTimer(hWnd, 1);

	SetWindowRgn(hInner, NULL, true);
	DeleteObject(winRect);

	// SFML throws exception with Layout deallocation
	
	//delete mwindow; 

	return msg.wParam;
}

VOID updateContext();

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOVING:
	case WM_SIZING:
	case WM_SIZE:
		adaptWindowRect(hWnd);
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		mouseDown = true;
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		winTransforming = Idle;
		mouseDown = false;
		break;
	case WM_TIMER:
		if (mouseDown)
		{
			if (mwindow != 0 && mwindow->isMaximized())
				return 0;

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
				MoveWindow(hWnd, posX, posY, rect.right - rect.left, rect.bottom - rect.top, true);
				break;
			}
			adaptWindowRect(hWnd);
		}
		break;
	case WM_MOUSEMOVE:
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
		else if (posX > wndRect.right - wndRect.left - BORDER_LEN * 2) {
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
		else if (posY > wndRect.bottom - wndRect.top - BORDER_LEN * 2) {
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

LRESULT CALLBACK InnProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hInner, &ps);
		updateContext();
		EndPaint(hInner, &ps);
		break;
	case WM_LBUTTONDOWN:
		mwindow->layout().executeOnMouseDown();
		mouseDown = true;
		break;
	case WM_RBUTTONDOWN:
		mwindow->layout().executeOnMouseDown();
		mouseDown = true;
		break;
	case WM_LBUTTONUP:
		mwindow->layout().executeOnMouseUp();
		winTransforming = Idle;
		mouseDown = false;
		break;
	case WM_RBUTTONUP:
		mwindow->layout().executeOnMouseRightButtonUp();
		winTransforming = Idle;
		mouseDown = false;
		break;
	case WM_MOUSEMOVE:
		mwindow->layout().executeOnMouseMove();

		if (mouseDown)
			return 0;

		if (mwindow != 0 && mwindow->isMaximized())
			return 0;

		offsetX = LOWORD(lParam) + 4;
		offsetY = HIWORD(lParam) + 4;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

VOID updateContext() {
	if (mwindow != 0)
		mwindow->layout().update();
}

#endif
