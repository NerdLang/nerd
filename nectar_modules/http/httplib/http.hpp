#include <App.h>

NectarCore::VAR __NJS_Create_Server()
{
	NectarCore::VAR app = new NectarCore::Class::Object();
	NectarCore::VAR conf = new NectarCore::Class::Object();
	
	conf["PORT"] = 8080;
	
	uWS::App* uws = new uWS::App();
	
	app["run"] = __Nectar_Create_Var_Scoped_Copy_Anon(
	{	
		uws->run();
		delete uws;
		return NectarCore::Global::undefined;
	});
	
	app["listen"] = __Nectar_Create_Var_Scoped_Copy_Anon(
	{
		if(__Nectar_VARLENGTH > 0) conf["PORT"] = __Nectar_VARARGS[0];
		if(__Nectar_VARLENGTH > 1) conf["LISTEN_CB"] = __Nectar_VARARGS[1];
		
		if(conf["PORT"].type != NectarCore::Enum::Type::Number)
		{
			throw(NectarCore::VAR(".listen method requires a number"));
		}
		
		uws->listen(conf["PORT"], [&](auto *token)
		{
			if (token)
			{
				if(conf["LISTEN_CB"]) conf["LISTEN_CB"]();
			}
			
		});

		return app;
	});
	
	app["get"] = __Nectar_Create_Var_Scoped_Copy_Anon(
	{
		NectarCore::VAR path;
		NectarCore::VAR cb;
		if(__Nectar_VARLENGTH > 0) path = __Nectar_VARARGS[0];
		if(__Nectar_VARLENGTH > 1) cb = __Nectar_VARARGS[1];
		
		if(cb.type == NectarCore::Enum::Type::Function)
		{
			uws->get(path, [=](auto *res, auto *req)
			{
				NectarCore::VAR _req = new NectarCore::Class::Object();
				NectarCore::VAR _res = new NectarCore::Class::Object();
				
				_res["write"] = __Nectar_Create_Var_Scoped_Anon(
				{
					if(__Nectar_VARLENGTH > 0) res->write(__Nectar_VARARGS[0]);
					else res->write("");
					return NectarCore::Global::undefined;
				});
				_res["end"] = __Nectar_Create_Var_Scoped_Anon(
				{
					if(__Nectar_VARLENGTH > 0) res->end(__Nectar_VARARGS[0]);
					else res->end();
					return NectarCore::Global::undefined;
				});
				cb(_req, _res);
			});
		}
		else if(cb.type == NectarCore::Enum::Type::String)
		{
			std::string s = cb;
			uws->get(path, [=](auto *res, auto *req)
			{
				res->end(s);
			});
		}
		else 
		{
			throw(NectarCore::VAR(".get method requires a function callback or a string"));
		}
		return app;
	});
	
	return app;
}
