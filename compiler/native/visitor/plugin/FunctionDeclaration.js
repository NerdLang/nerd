var FunctionDeclaration=
{
	enter(_path)
	{
		_path.node.VAR = {var:[], const:[]};
		if(_path.node.id)
		{
			COMPILER.VAR_STATE.push([]);
			VISITOR.pushDeclVar(_path.node.id.name, 0);
			
			VISITOR.CURRENT_Function++;
			VISITOR.Function_STATE.push(_path.node.id.name);
			
			if(!COMPILER.INFO.SCOPE[_path.node.id.name]) COMPILER.INFO.SCOPE[_path.node.id.name] = {init:[], use:[], call:[], param: [], fast: true};
			VISITOR.addFunctionVarInit(_path.node.id.name);
			if(_path.node.params.length > 0)
			{
				for(var i = 0; i < _path.node.params.length; i++)
				{
					VISITOR.addFunctionVarInit(_path.node.params[i].name);
				}
			}
		}
		
	},
	exit(_path)
	{
		var _hoistingVar = "";
		for(var i = 0; i < _path.node.VAR.var.length; i++)
		{
			_hoistingVar += "var " + _path.node.VAR.var[i] + ";";
		}
		for(var i = 0; i < _path.node.VAR.const.length; i++)
		{
			_hoistingVar += "__Nectar_CONST " + _path.node.VAR.const[i] + ";";
		}
		if(_hoistingVar.length > 0) _path.node.body.body.splice(0, 0, babel.parse(_hoistingVar));
		if(_path.node.id)
		{
			VISITOR.CURRENT_Function--;
			VISITOR.Function_STATE.pop();
			COMPILER.VAR_STATE.pop();
		}
	},
}
module.exports = FunctionDeclaration;