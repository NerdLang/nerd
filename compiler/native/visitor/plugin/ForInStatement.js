function ForInStatement(_path)
{
	var _rnd = RND();
	var _count = RND();
	var _left = _path.node.left.declarations[0].id.name;
	var _right = _path.node.right.name;
	var _pre = "var " + _rnd + " = __Nectar_Object_Keys(" + _right + ");";
	var _loop = `for(var ${_count} = 0; ${_count} < ${_rnd}.length; ${_count}++){var ${_left} = ${_rnd}[${_count}];`
	var _body = babel.generate(_path.node.body).code;
	var _end = "";
	if(_body[0] == "{")
	{
		_body = _body.substring(1);
	}
	else _end = "}";
	_loop += _body + _end;
	_path.insertBefore(babel.parse(_pre));
	_path.replaceWith(babel.parse(_loop));
}
module.exports = ForInStatement;