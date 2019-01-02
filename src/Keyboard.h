#pragma once

#include "Window.h"

namespace Magenta
{
	enum KeyCode {
		Key_LeftButton,
		Key_RightButton,
		Key_Cancel,
		Key_Back,
		Key_Tab,
		Key_Enter,
		Key_Shift,
		Key_Control,
		Key_Alt,
		Key_Pause,
		Key_CapsLock,
		Key_Escape,
		Key_Space,
		Key_PageUp,
		Key_PageDown,
		Key_End,
		Key_Home,
		Key_Left,
		Key_Top,
		Key_Right,
		Key_Bottom,
		Key_Select,
		Key_Print,
		Key_PrintScreen,
		Key_Insert,
		Key_Delete,
		Key_1,
		Key_2,
		Key_3,
		Key_4,
		Key_5,
		Key_6,
		Key_7,
		Key_8,
		Key_9,
		Key_0,
		Key_A,
		Key_B,
		Key_C,
		Key_D,
		Key_E,
		Key_F,
		Key_G,
		Key_H,
		Key_I,
		Key_J,
		Key_K,
		Key_L,
		Key_M,
		Key_N,
		Key_O,
		Key_P,
		Key_Q,
		Key_R,
		Key_S,
		Key_T,
		Key_U,
		Key_V,
		Key_W,
		Key_X,
		Key_Y,
		Key_Z,
		Key_Win,
		Key_F1,
		Key_F2,
		Key_F3,
		Key_F4,
		Key_F5,
		Key_F6,
		Key_F7,
		Key_F8,
		Key_F9,
		Key_F10,
		Key_F11,
		Key_F12,
		Key_NumLock,
		Key_LeftShift,
		Key_RightShift,
		Key_LeftControl,
		Key_RightControl,
		Key_LeftAlt,
		Key_RightAlt,
		Key_Undefined
	};

	KeyCode keyCodeFromWin32(short keyCode);

	const unsigned int NotCharacterKey = 0;

	unsigned int keyCodeToCharacterWin32(KeyCode keyCode, Window* window);
	unsigned int keyCodeToCharacter(KeyCode keyCode, Window* window);
}
