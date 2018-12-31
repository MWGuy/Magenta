#pragma once

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
