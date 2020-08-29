/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#include "webview.h"

function __NJS_LAUNCH_WEBVIEW(content, title, width, height)
{
	if(content.type == __NJS_UNDEFINED) content = "data:text/html,<html><body><h1>Hello Nectar !</h1></body></html>";
	if(title.type == __NJS_UNDEFINED) title = "NectarJS WebView";
	if(width.type == __NJS_UNDEFINED) width = 600;
	if(height.type == __NJS_UNDEFINED) height = 400;;
	webview::webview w(true, nullptr);
	w.set_title(title.get().s->value);
	w.set_size(width.get().i, height.get().i, WEBVIEW_HINT_NONE);
	w.navigate(content.get().s->value);
	w.run();
}
