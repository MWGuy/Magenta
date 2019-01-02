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
