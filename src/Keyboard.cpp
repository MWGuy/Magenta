#include "Keyboard.h"
#include "Window.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace Magenta
{
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
		case 0xBA: return Key_OEM_1; break;
		case 0xE2: return Key_OEM_102; break;
		case 0xBF: return Key_OEM_2; break;
		case 0xC0: return Key_OEM_3; break;
		case 0xDB: return Key_OEM_4; break;
		case 0xDC: return Key_OEM_5; break;
		case 0xDD: return Key_OEM_6; break;
		case 0xDE: return Key_OEM_7; break;
		case 0xDF: return Key_OEM_8; break;
		case 0xBD: return Key_OEM_Minus; break;
		case 0xBC: return Key_OEM_Comma; break;
		case 0xBE: return Key_OEM_Period; break;
		case 0xBB: return Key_OEM_Plus; break;
		}
	}

#ifdef _WIN32
	unsigned int characterToWin32(KeyCode keyCode)
	{
		switch (keyCode)
		{
		default: return 0;
		case Key_1: return 0x30; break;
		case Key_2: return 0x31; break;
		case Key_3: return 0x32; break;
		case Key_4: return 0x33; break;
		case Key_5: return 0x34; break;
		case Key_6: return 0x35; break;
		case Key_7: return 0x36; break;
		case Key_8: return 0x37; break;
		case Key_9: return 0x38; break;
		case Key_0: return 0x39; break;
		case Key_A: return 0x41; break;
		case Key_B: return 0x42; break;
		case Key_C: return 0x43; break;
		case Key_D: return 0x44; break;
		case Key_E: return 0x45; break;
		case Key_F: return 0x46; break;
		case Key_G: return 0x47; break;
		case Key_H: return 0x48; break;
		case Key_I: return 0x49; break;
		case Key_J: return 0x4A; break;
		case Key_K: return 0x4B; break;
		case Key_L: return 0x4C; break;
		case Key_M: return 0x4D; break;
		case Key_N: return 0x4E; break;
		case Key_O: return 0x4F; break;
		case Key_P: return 0x50; break;
		case Key_Q: return 0x51; break;
		case Key_R: return 0x52; break;
		case Key_S: return 0x53; break;
		case Key_T: return 0x54; break;
		case Key_U: return 0x55; break;
		case Key_V: return 0x56; break;
		case Key_W: return 0x57; break;
		case Key_X: return 0x58; break;
		case Key_Y: return 0x59; break;
		case Key_Z: return 0x5A; break;
		case Key_OEM_1: return 0xBA; break;
		case Key_OEM_102: return 0xE2; break;
		case Key_OEM_2: return 0xBF; break;
		case Key_OEM_3: return 0xC0; break;
		case Key_OEM_4: return 0xDB; break;
		case Key_OEM_5: return 0xDC; break;
		case Key_OEM_6: return 0xDD; break;
		case Key_OEM_7: return 0xDE; break;
		case Key_OEM_8: return 0xDF; break;
		case Key_OEM_Minus: return 0xBD; break;
		case Key_OEM_Comma: return 0xBC; break;
		case Key_OEM_Period: return 0xBE; break;
		case Key_OEM_Plus: return 0xBB; break;
		}
	}
#endif

	unsigned int keyCodeToCharacterWin32(KeyCode keyCode, Window* window)
	{
#ifdef _WIN32
		unsigned int code = characterToWin32(keyCode);
		HKL hKl = GetKeyboardLayout(GetWindowThreadProcessId(window->handler(), 0));
		return code == 0 ? 0 : MapVirtualKeyEx(characterToWin32(keyCode), MAPVK_VK_TO_CHAR, hKl);
#else
		return 0;
#endif

	}

	unsigned int keyCodeToCharacter(KeyCode keyCode, Window* window)
	{
#ifdef _WIN32
		return keyCodeToCharacterWin32(keyCode, window);
#elif _OSX
		return 0;
#endif
	}
}
