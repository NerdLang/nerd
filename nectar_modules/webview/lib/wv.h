#include "webview.h"

function __NJS_LAUNCH_WEBVIEW(content, title, width, height)
{
	if(content.type == __NJS_UNDEFINED) content = "data:text/html,<html><body><h1>Hello Nectar !</h1></body></html>";
	if(title.type == __NJS_UNDEFINED) title = "NectarJS WebView";
	if(width.type == __NJS_UNDEFINED) width = 600;
	if(height.type == __NJS_UNDEFINED) height = 400;;
	webview::webview w(true, nullptr);
	w.set_title(title.get().s->__NJS_VALUE);
	w.set_size(width.get().i, height.get().i, WEBVIEW_HINT_NONE);
	w.navigate(content.get().s->__NJS_VALUE);
	w.run();
}
