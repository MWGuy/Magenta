#pragma once

#include "Keyboard.h"
#include <vector>

#define EventUnset 0

namespace Magenta
{
	class Window;
	class Widget;

	typedef void(*EventCallback)(Widget& self);

	class EventHandler {
		std::vector<EventCallback> widgetSpecificCallbacks;
		std::vector<EventCallback> sequence;
		Widget* mAssignedWidget;
	public:
		void operator+=(EventCallback callback);
		void operator=(EventCallback callback);
		void setWidgetSpecific(EventCallback callback);
		Widget& assignedWidget();

		void dispatch();

		EventHandler(Widget* assignedTo);
	};

	typedef EventHandler MouseEventHandler;
	typedef EventHandler WidgetEventHandler;

	typedef void(*KeyboardEventCallback)(Widget& self, KeyCode key);

	class KeyboardEventHandler {
		std::vector<KeyboardEventCallback> widgetSpecificCallbacks;
		std::vector<KeyboardEventCallback> sequence;
		Widget* mAssignedWidget;
	public:
		void operator+=(KeyboardEventCallback callback);
		void operator=(KeyboardEventCallback callback);
		void setWidgetSpecific(KeyboardEventCallback callback);
		Widget& assignedWidget();

		void dispatch(KeyCode keyCode);

		KeyboardEventHandler(Widget* assignedTo);
	};

	typedef void(*KeyboardInputEventCallback)(Widget& self, char character);

	class KeyboardInputEventHandler {
		std::vector<KeyboardInputEventCallback> widgetSpecificCallbacks;
		std::vector<KeyboardInputEventCallback> sequence;
		Widget* mAssignedWidget;
	public:
		void operator+=(KeyboardInputEventCallback callback);
		void operator=(KeyboardInputEventCallback callback);
		void setWidgetSpecific(KeyboardInputEventCallback callback);
		Widget& assignedWidget();

		void dispatch(char character);

		KeyboardInputEventHandler(Widget* assignedTo);
	};

	typedef void(*WindowEventCallback)(Window& self);

	class WindowEventHandler {
		std::vector<WindowEventCallback> sequence;
		Window* mAssignedWindow;
	public:
		void operator+=(WindowEventCallback callback);
		void operator=(WindowEventCallback callback);
		Window& assignedWindow();

		void dispatch();

		WindowEventHandler(Window* assignedTo);
	};

	class SharedEventCallback {
	public:
		EventCallback callback;
		Widget& selfArg;

		SharedEventCallback(EventCallback aCallback, Widget& aSelfArg);
	};

	class SharedEventHandler {
		std::vector<SharedEventCallback*> sequence;
	public:
		void operator+=(SharedEventCallback* callback);
		void operator-=(SharedEventCallback* callback);

		void dispatchAll();

		SharedEventHandler();
	};
}
