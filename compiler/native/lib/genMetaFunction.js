global.RND = function() { return "__META_" + Math.random().toString(36).substring(7); };

function genMetaFunction(_code)
{	
    var _return = ";return __NJS_Create_Undefined();}";
    var _searchFN = new RegExp(/function (.[a-zA-Z0-9_\-]*) *\((.*)\)/);
    var _index = _code.search(_searchFN);
    while(_index > -1)
    {
        var _genFN = "__NJS_FN_" + RND();
        var _count = 0;
        var _start = -1;
        var _end = -1;
    
        let _match = _searchFN.exec(_code);

        _match[2] = _match[2].split(",");
        var _getVar = "";
        for(var i = 0; i < _match[2].length; i++)
        {
            if(_match[2][i].length > 0)
            {
                _getVar += `var ${_match[2][i]}; if(__NJS_VARARGS.size() > ${i}) ${_match[2][i]} = __NJS_VARARGS[${i}];`;
            }
        }
        for(var i = _index; i < _code.length; i++)
        {
                if(_code[i] == "{")
                {
                        if(_start == -1) _start = i;
                        _count++;
                }
                else if(_code[i] == "}")
                {
                    
                    _end = i;
                    _count--;
                    if(_count == 0)
                    {
                        var _fn = "{" + _getVar + _code.substring(_start + 1, _end);
                        var _catch = "";
                        if(_code.indexOf("'SCOPED_FUNCTION';") > -1) _catch = "=";
                        else if(_code.indexOf("\"SCOPED_FUNCTION\";") > -1) _catch = "=";

                        var _formated = "__NJS_DECL_FUNCTION<__NJS_VAR (vector<var>)>* " + _genFN +" = new __NJS_DECL_FUNCTION<__NJS_VAR (vector<var>)>([" + _catch + "]( vector<var> __NJS_VARARGS ) -> __NJS_VAR" + _fn + _return + ");";
                        _formated += "var " + _match[1] + "=__NJS_VAR(__NJS_FUNCTION, " + _genFN + ");";                        
                        _code = [_code.slice(0, _index), _formated, _code.slice(_end + 1)].join('');
                        break;
                    }
                }
        }
        _index = _code.search(_searchFN);
    }
    return _code;
}

module.exports = genMetaFunction;