#include "WindowCaption.h"

namespace Magenta
{
	void dragWindow(Widget& self) {
		self.layout()->getWindow()->setTransform(Moving);
	}

	WindowCaption_::WindowCaption_(Layout* aLayout, Widget* aParent, unsigned long aId)
		: Widget(aLayout, aParent, aId)
	{
		onmousedown.setWidgetSpecific(dragWindow);
	}

	void WindowCaption_::draw() 
	{
#ifdef _WIN32
		Gdiplus::Graphics graphics(layout()->view);
		Gdiplus::Rect rect;
		rect.X = computedRect().left;
		rect.Y = computedRect().top;
		rect.Width = computedRect().width();
		rect.Height = computedRect().height();
		Gdiplus::SolidBrush br(Gdiplus::Color(40, 161, 105, 227));
		graphics.FillRectangle(&br, rect);
#endif
		drawChilds();
	}

	WindowCaption createWindowCaption(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new WindowCaption_(owner.layout(), &owner, aId));
		return (WindowCaption)*owner.childs[owner.childs.size() - 1];
	}
}
