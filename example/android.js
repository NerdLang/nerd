var _tpl = "Text: <input id='test' type='text' /><br>";
_tpl += "<button onClick='Nectar.fireEvent(document.getElementById(\"test\").value);'>{{CONTENT}}</button>";

android.draw(_tpl.replace("{{CONTENT}}", "Hello NectarJS !"));

android.onEvent = function(_event)
{
    android.draw(_tpl.replace("{{CONTENT}}", _event));
};