#pragma once

#include <vector>

#define EventUnset 0

namespace Magenta
{
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

	typedef void(*EventCallback)(Widget& self);

	class GlobalEventCallback {
	public:
		EventCallback callback;
		Widget& selfArg;

		GlobalEventCallback(EventCallback aCallback, Widget& aSelfArg);
	};

	class SharedEventHandler {
		std::vector<GlobalEventCallback*> sequence;
	public:
		void operator+=(GlobalEventCallback* callback);
		void operator-=(GlobalEventCallback* callback);

		void dispatchAll();

		SharedEventHandler();
	};
}
