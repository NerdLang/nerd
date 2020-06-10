var _tpl = "<h1>{{CONTENT}}</h1><br>Text: <input id='test' type='text' /><br>";
_tpl += "<button onClick='Nectar.fireEvent(document.getElementById(\"test\").value);'>Update</button>";

iOS.draw(_tpl.replace("{{CONTENT}}", "Hello NectarJS !"));

iOS.onEvent = function(_event)
{
    iOS.draw(_tpl.replace("{{CONTENT}}", _event));
};