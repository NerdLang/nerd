var Linter = require("eslint").Linter;
var linter = new Linter();

function nectarLint(_code, _file, _expose)
{
    var _fatal = false;
    if(!COMPILER.ENV.check.globals) COMPILER.ENV.check.globals = {};

    if(_expose)
    {
        for(var i = 0; i < _expose.length; i++)
        {
            COMPILER.ENV.check.globals[_expose[i]] = false;
        }
    }

    var _res = linter.verify(_code, COMPILER.ENV.check, { filename: _file });
    for(var i = 0; i < _res.length; i++)
    {
        if(_res[i].severity > 1) 
        {
            _fatal = true;
            console.log("[error]", _res[i].message, "line", _res[i].line, "column", _res[i].column, "in file", _file);
        }
        else console.log("[warning]", _res[i].message, "line", _res[i].line, "column", _res[i].column, "in file", _file);
    }
    if(_fatal) process.exit(1);
}

module.exports = nectarLint;
