var webview = require("webview");

var content = "data:text/html,<html><body><h1>Hello Nectar !</h1></body></html>";
var title = "NectarJS App";

webview.launch(content, title);
