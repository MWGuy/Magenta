#include "AppWindowF.h"

using namespace Magenta;

namespace MagentaForm
{
	void w_close(Widget& self) {
		self.layout()->getWindow()->close();
	}
	void w_maximize(Widget& self) {
		self.layout()->getWindow()->toggleMaximize();
	}
	void w_minimize(Widget& self) {
		self.layout()->getWindow()->minimize();
	}

	void AppWindowF ma_form
	{
		// Window caption

		WindowCaption caption = createWindowCaption(view, id_caption);
		caption.width$ = 100;
		caption.height = 34;
		WindowCaptionInner captionInner = createWindowCaptionInner(caption, id_caption_inner);
		captionInner.width$ = 100;
		captionInner.height = 31;

		// System buttons

#ifndef _OSX

		Frame sysbutton_close = createFrame(captionInner, id_sysbutton_close);
		sysbutton_close.position = CenterRight;
		sysbutton_close.width = 21;
		sysbutton_close.height = 21;
		sysbutton_close.x = -4;
		sysbutton_close.onclick = w_close;

		Frame sysbutton_maximize = createFrame(captionInner, id_sysbutton_maximize);
		sysbutton_maximize.position = CenterRight;
		sysbutton_maximize.width = 21;
		sysbutton_maximize.height = 21;
		sysbutton_maximize.x = -31;
		sysbutton_maximize.onclick = w_maximize;

		Frame sysbutton_minimize = createFrame(captionInner, id_sysbutton_minimize);
		sysbutton_minimize.position = CenterRight;
		sysbutton_minimize.width = 21;
		sysbutton_minimize.height = 21;
		sysbutton_minimize.x = -58;
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

		Frame n2view = createFrame(view, id_n2view);
		n2view.width$ = 100;
		n2view.height$ = 100;
		n2view.height = -31;
		n2view.y = 31;

		Frame panel = createFrame(view, id_panel);
		panel.width$ = 100;
		panel.height = 39;
		panel.zIndex = 1;
		panel.y = 31;

		// Panel controls

		Frame backward = createFrame(panel, id_backward);
		backward.position = CenterLeft;
		backward.width = 21;
		backward.height = 21;
		backward.x = 8;

		Frame forward = createFrame(panel, id_forward);
		forward.position = CenterLeft;
		forward.width = 21;
		forward.height = 21;
		forward.x = 38;

		Frame menu = createFrame(panel, id_menu);
		menu.position = CenterRight;
		menu.width = 21;
		menu.height = 21;
		menu.x = -14;
		menu.onclick = removeWidget;

		Frame addressbar = createFrame(panel, id_addressbar);
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
