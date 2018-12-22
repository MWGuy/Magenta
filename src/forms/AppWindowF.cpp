#include "AppWindowF.h"

using namespace Magenta;

namespace MagentaForm
{
	void AppWindowF ma_form
	{
		Frame frame = createFrame(view);
		frame.position = BottomCenter;
		frame.relativeWidth = 50;
		frame.height = 120;
		frame.y = -40;
		frame.onrightclick = removeWidget;
	}

}
