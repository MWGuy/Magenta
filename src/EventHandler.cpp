#include "EventHandler.h"
#include "Widget.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace Magenta
{
	void EventHandler::operator+=(EventCallback callback) {
		sequence.push_back(callback);
	}

	void EventHandler::operator=(EventCallback callback)
	{
		sequence.clear();
		sequence.push_back(callback);
	}

	void EventHandler::setWidgetSpecific(EventCallback callback) {
		widgetSpecificCallbacks.push_back(callback);
	}

	Widget& EventHandler::assignedWidget() {
		return *mAssignedWidget;
	}

	void EventHandler::dispatch() {
		for (size_t i = 0; i < widgetSpecificCallbacks.size(); i++)
			widgetSpecificCallbacks[i](*mAssignedWidget);

		for (size_t i = 0; i < sequence.size(); i++)
			sequence[i](*mAssignedWidget);
	}

	KeyCode keyCodeFromWin32(short keyCode)
	{
		switch (keyCode)
		{
		default: return Key_Undefined; break;
		case 0x01: return Key_LeftButton; break;
		case 0x02: return Key_RightButton; break;
		case 0x03: return Key_Cancel; break;
		case 0x08: return Key_Back; break;
		case 0x09: return Key_Tab; break;
		case 0x0D: return Key_Enter; break;
		case 0x10: return Key_Shift; break;
		case 0x11: return Key_Control; break;
		case 0x12: return Key_Alt; break;
		case 0x13: return Key_Pause; break;
		case 0x14: return Key_CapsLock; break;
		case 0x1B: return Key_Escape; break;
		case 0x20: return Key_Space; break;
		case 0x21: return Key_PageUp; break;
		case 0x22: return Key_PageDown; break;
		case 0x23: return Key_End; break;
		case 0x24: return Key_Home; break;
		case 0x25: return Key_Left; break;
		case 0x26: return Key_Top; break;
		case 0x27: return Key_Right; break;
		case 0x28: return Key_Bottom; break;
		case 0x29: return Key_Select; break;
		case 0x2A: return Key_Print; break;
		case 0x2C: return Key_PrintScreen; break;
		case 0x2D: return Key_Insert; break;
		case 0x2E: return Key_Delete; break;
		case 0x30: return Key_1; break;
		case 0x31: return Key_2; break;
		case 0x32: return Key_3; break;
		case 0x33: return Key_4; break;
		case 0x34: return Key_5; break;
		case 0x35: return Key_6; break;
		case 0x36: return Key_7; break;
		case 0x37: return Key_8; break;
		case 0x38: return Key_9; break;
		case 0x39: return Key_0; break;
		case 0x41: return Key_A; break;
		case 0x42: return Key_B; break;
		case 0x43: return Key_C; break;
		case 0x44: return Key_D; break;
		case 0x45: return Key_E; break;
		case 0x46: return Key_F; break;
		case 0x47: return Key_G; break;
		case 0x48: return Key_H; break;
		case 0x49: return Key_I; break;
		case 0x4A: return Key_J; break;
		case 0x4B: return Key_K; break;
		case 0x4C: return Key_L; break;
		case 0x4D: return Key_M; break;
		case 0x4E: return Key_N; break;
		case 0x4F: return Key_O; break;
		case 0x50: return Key_P; break;
		case 0x51: return Key_Q; break;
		case 0x52: return Key_R; break;
		case 0x53: return Key_S; break;
		case 0x54: return Key_T; break;
		case 0x55: return Key_U; break;
		case 0x56: return Key_V; break;
		case 0x57: return Key_W; break;
		case 0x58: return Key_X; break;
		case 0x59: return Key_Y; break;
		case 0x5A: return Key_Z; break;
		case 0x5B: return Key_Win; break;
		case 0x70: return Key_F1; break;
		case 0x71: return Key_F2; break;
		case 0x72: return Key_F3; break;
		case 0x73: return Key_F4; break;
		case 0x74: return Key_F5; break;
		case 0x75: return Key_F6; break;
		case 0x76: return Key_F7; break;
		case 0x77: return Key_F8; break;
		case 0x78: return Key_F9; break;
		case 0x79: return Key_F10; break;
		case 0x7A: return Key_F11; break;
		case 0x7B: return Key_F12; break;
		case 0x90: return Key_NumLock; break;
		case 0xA0: return Key_LeftShift; break;
		case 0xA1: return Key_RightShift; break;
		case 0xA2: return Key_LeftControl; break;
		case 0xA3: return Key_RightControl; break;
		case 0xA4: return Key_LeftAlt; break;
		case 0xA5: return Key_RightAlt; break;
		}
	}

	void KeyboardEventHandler::operator+=(KeyboardEventCallback callback)
	{
		sequence.push_back(callback);
	}
	void KeyboardEventHandler::operator=(KeyboardEventCallback callback)
	{
		sequence.clear();
		sequence.push_back(callback);
	}

	void KeyboardEventHandler::setWidgetSpecific(KeyboardEventCallback callback) {
		widgetSpecificCallbacks.push_back(callback);
	}

	Widget& KeyboardEventHandler::assignedWidget() {
		return *mAssignedWidget;
	}

	void KeyboardEventHandler::dispatch(KeyCode keyCode) {
		for (size_t i = 0; i < widgetSpecificCallbacks.size(); i++)
			widgetSpecificCallbacks[i](*mAssignedWidget, keyCode);

		for (size_t i = 0; i < sequence.size(); i++)
			sequence[i](*mAssignedWidget, keyCode);
	}

	KeyboardEventHandler::KeyboardEventHandler(Widget* assignedTo) : mAssignedWidget(assignedTo)
	{
	}

	void WindowEventHandler::operator+=(WindowEventCallback callback) {
		sequence.push_back(callback);
	}

	void WindowEventHandler::operator=(WindowEventCallback callback)
	{
		sequence.clear();
		sequence.push_back(callback);
	}

	Window& WindowEventHandler::assignedWindow() {
		return *mAssignedWindow;
	}

	void WindowEventHandler::dispatch()
	{
		for (size_t i = 0; i < sequence.size(); i++)
			sequence[i](*mAssignedWindow);
	}

	WindowEventHandler::WindowEventHandler(Window* assignedTo) : mAssignedWindow(assignedTo)
	{
	}

	EventHandler::EventHandler(Widget* assignedTo) : mAssignedWidget(assignedTo)
	{
	}

	SharedEventCallback::SharedEventCallback(EventCallback aCallback, Widget& aSelfArg) : callback(aCallback), selfArg(aSelfArg)
	{
	}
	
	void SharedEventHandler::operator+=(SharedEventCallback* callback)
	{
		sequence.push_back(callback);
	}

	void SharedEventHandler::operator-=(SharedEventCallback* callback)
	{
		for (size_t i = 0; i < sequence.size(); i++) {
			if (sequence[i] == callback)
			{
				sequence.erase(sequence.begin() + i);
				break;
			}
		}
	}

	void SharedEventHandler::dispatchAll()
	{
		for (size_t i = 0; i < sequence.size(); i++) {
			sequence[i]->callback(sequence[i]->selfArg);
		}
	}

	SharedEventHandler::SharedEventHandler()
	{
	}
}
