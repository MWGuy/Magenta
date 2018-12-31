#include "AppWindowF.h"

using namespace Magenta;

namespace MagentaForm
{
	void w_close(Widget& self) {
		self.layout()->getWindow()->close();
	}
	void w_maximize(Widget& self) {
		self.layout()->getWindow()->toggleMaximize();
		
		ActionButton_& ab = (ActionButton_&)self;
		ab.state = 0;

		if (self.layout()->getWindow()->isMaximized())
		{
			ab.figNormal = Figure("resources/sysbuttons.png", 0, 62, 31, 31);
			ab.figHover = Figure("resources/sysbuttons.png", 31, 62, 31, 31);
			ab.figPress = Figure("resources/sysbuttons.png", 62, 62, 31, 31);
			self.layout()->findWidgetById(id_sysbutton_close)->x = 0;
			self.layout()->findWidgetById(id_sysbutton_maximize)->x = -31;
			self.layout()->findWidgetById(id_sysbutton_minimize)->x = -62;
		}
		else
		{
			ab.figNormal = Figure("resources/sysbuttons.png", 0, 31, 31, 31);
			ab.figHover = Figure("resources/sysbuttons.png", 31, 31, 31, 31);
			ab.figPress = Figure("resources/sysbuttons.png", 62, 31, 31, 31);
			self.layout()->findWidgetById(id_sysbutton_close)->x = -6;
			self.layout()->findWidgetById(id_sysbutton_maximize)->x = -37;
			self.layout()->findWidgetById(id_sysbutton_minimize)->x = -69;
		}
	}
	void w_minimize(Widget& self) {
		self.layout()->getWindow()->minimize();
	}

	void toggleOpenMenu(Widget& self) {
		//self.layout()->findWidgetById(id_menu_popup)->toggleVisibility();
	}

	void AppWindowF ma_form
	{
		// Window caption

		WindowCaption caption = createWindowCaption(view, id_caption);
		caption.width$ = 100;
		caption.height = 35;
		WindowCaptionInner captionInner = createWindowCaptionInner(caption, id_caption_inner);
		captionInner.width$ = 100;
		captionInner.height = 31;

		// System buttons

#ifndef _OSX

		ActionButton sysbutton_close = createActionButton(captionInner, id_sysbutton_close,
			Figure("resources/sysbuttons.png", 0, 0, 31, 31),  // normal
			Figure("resources/sysbuttons.png", 31, 0, 31, 31), // hover
			Figure("resources/sysbuttons.png", 62, 0, 31, 31)  // press
		);
		sysbutton_close.position = CenterRight;
		sysbutton_close.width = 31;
		sysbutton_close.height = 31;
		sysbutton_close.x = 0;
		sysbutton_close.onclick = w_close;

		ActionButton sysbutton_maximize = createActionButton(captionInner, id_sysbutton_maximize,
			Figure("resources/sysbuttons.png", 0, 62, 31, 31),  // normal
			Figure("resources/sysbuttons.png", 31, 62, 31, 31), // hover
			Figure("resources/sysbuttons.png", 62, 62, 31, 31)  // press
		);
		sysbutton_maximize.position = CenterRight;
		sysbutton_maximize.width = 31;
		sysbutton_maximize.height = 31;
		sysbutton_maximize.x = -31;
		sysbutton_maximize.onclick = w_maximize;

		ActionButton sysbutton_minimize = createActionButton(captionInner, id_sysbutton_minimize,
			Figure("resources/sysbuttons.png", 0, 93, 31, 31),  // normal
			Figure("resources/sysbuttons.png", 31, 93, 31, 31), // hover
			Figure("resources/sysbuttons.png", 62, 93, 31, 31)  // press
		);
		sysbutton_minimize.position = CenterRight;
		sysbutton_minimize.width = 31;
		sysbutton_minimize.height = 31;
		sysbutton_minimize.x = -62;
		sysbutton_minimize.onclick = w_minimize;

#else
		// macOS system buttons
#endif

		// Tab zone with tabs

		TabRegion tabregion = createTabRegion(captionInner, id_tabregion);
		tabregion.position = BottomLeft;
		tabregion.width$ = 100;
		tabregion.width = -112;
		tabregion.height = 28;
#ifndef _OSX
		tabregion.x = 12;
#else
		// Indent for macOS system buttons
#endif

		// Base controls

		NewtooView n2view = createNewtooView(view, id_n2view);
		n2view.width$ = 100;
		n2view.height$ = 100;
		n2view.height = -36;
		n2view.y = 36;

		TopPanel panel = createTopPanel(view, id_panel);
		panel.width$ = 100;
		panel.height = 39;
		panel.zIndex = 1;
		panel.y = 31;

		// Panel controls

		PanelButton backward = createPanelButton(panel, id_backward,
			Figure("resources/panel.png", 0, 56, 56, 56)
		);
		backward.position = CenterLeft;
		backward.width = 21;
		backward.height = 21;
		backward.x = 8;

		PanelButton forward = createPanelButton(panel, id_forward,
			Figure("resources/panel.png", 56, 0, 56, 56)
		);
		forward.position = CenterLeft;
		forward.width = 21;
		forward.height = 21;
		forward.x = 38;

		PanelButton menu = createPanelButton(panel, id_menu,
			Figure("resources/panel.png", 112, 0, 56, 56)
		);
		menu.position = CenterRight;
		menu.width = 21;
		menu.height = 21;
		menu.x = -14;
		menu.onclick = toggleOpenMenu;

		Frame menuPopup = createFrame(view, id_menu_popup);
		menuPopup.zIndex = 10;
		menuPopup.position = TopRight;
		menuPopup.width = 188;
		menuPopup.height = 260;
		menuPopup.y = 60;
		menuPopup.x = -4;
		menuPopup.hide();

		AddressBar addressbar = createAddressBar(panel, id_addressbar);
		addressbar.position = CenterLeft;
		addressbar.width$ = 100;
		addressbar.width -= 146;
		addressbar.height = 31;
		addressbar.x = 73;

		Frame connection_icon = createFrame(addressbar, id_connection_icon);
		connection_icon.position = CenterLeft;
		connection_icon.width = 16;
		connection_icon.height = 16;
		connection_icon.x = 8;

		Frame refresh = createFrame(addressbar, id_refresh);
		refresh.position = CenterRight;
		refresh.width = 18;
		refresh.height = 18;
		refresh.x -= 8;

		Frame bookmark = createFrame(addressbar, id_bookmark);
		bookmark.position = CenterRight;
		bookmark.width = 16;
		bookmark.height = 16;
		bookmark.x -= 32;

		Frame address = createFrame(addressbar, id_bookmark);
		address.position = TopLeft;
		address.width$ = 100;
		address.width -= 92;
		address.height = 31;
		address.x = 32;


	}



}
