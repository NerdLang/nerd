var _tpl = "<h1>{{CONTENT}}</h1><br>Text: <input id='test' type='text' /><br>";
_tpl += "<button onClick='Nectar.fireEvent(document.getElementById(\"test\").value);'>Update</button>";

Nectar.draw(_tpl.replace("{{CONTENT}}", "Hello NectarJS !"));

Nectar.onEvent = function(_event)
{
    Nectar.draw(_tpl.replace("{{CONTENT}}", _event));
};