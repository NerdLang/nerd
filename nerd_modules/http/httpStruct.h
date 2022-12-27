var __LAZY_RES_STATUS = __NERD_Create_Var_Unscoped_Anon(
{
	var arg;
	if(__NERD_VARLENGTH > 0)
	{
		arg = __NERD_VARARGS[0];
	}
	((uWS::HttpResponse<false>*)__NERD_OBJECT(__NERD_THIS)->bind)->writeStatus((std::string)arg);
	return NerdCore::Global::null;
});

var __LAZY_RES_HEADER = __NERD_Create_Var_Unscoped_Anon(
{
	var arg1;
	var arg2;
	if(__NERD_VARLENGTH > 0)
	{
		arg1 = __NERD_VARARGS[0];
	}
	if(__NERD_VARLENGTH > 1)
	{
		arg2 = __NERD_VARARGS[1];
	}
	((uWS::HttpResponse<false>*)__NERD_OBJECT(__NERD_THIS)->bind)->writeHeader((std::string)arg1, (std::string)arg2);
	return NerdCore::Global::null;
});

var __LAZY_RES_WRITE = __NERD_Create_Var_Unscoped_Anon(
{
	var arg;
	if(__NERD_VARLENGTH > 0)
	{
		arg = __NERD_VARARGS[0];
	}
	
	((uWS::HttpResponse<false>*)__NERD_OBJECT(__NERD_THIS)->bind)->write((std::string)arg);
	return NerdCore::Global::null;
});

var __LAZY_RES_END = __NERD_Create_Var_Unscoped_Anon(
{
	var arg;
	if(__NERD_VARLENGTH > 0)
	{
		arg = __NERD_VARARGS[0];
	}
	((uWS::HttpResponse<false>*)__NERD_OBJECT(__NERD_THIS)->bind)->end((std::string)arg);
	return NerdCore::Global::null;
});

var __LAZY_REQ_METHOD = __NERD_Create_Var_Unscoped_Anon(
{
	return ((uWS::HttpRequest*)__NERD_OBJECT(__NERD_THIS)->bind)->getMethod();
});

var __LAZY_REQ_HEADER = __NERD_Create_Var_Unscoped_Anon(
{
	var arg;
	if(__NERD_VARLENGTH > 0)
	{
		arg = __NERD_VARARGS[0];
	}
	return ((uWS::HttpRequest*)__NERD_OBJECT(__NERD_THIS)->bind)->getHeader((std::string)arg);
});

var __LAZY_REQ_URL = __NERD_Create_Var_Unscoped_Anon(
{
	return ((uWS::HttpRequest*)__NERD_OBJECT(__NERD_THIS)->bind)->getUrl();
});

struct __Nerd_HttpStruct
{
	var resStatus =__LAZY_RES_STATUS;
	var resHeader = __LAZY_RES_HEADER;
	var resWrite = __LAZY_RES_WRITE;
	var resEnd = __LAZY_RES_END;
	var reqMethod = __LAZY_REQ_METHOD;
	var reqHeader = __LAZY_REQ_HEADER;
	var reqUrl = __LAZY_REQ_URL;
} ;
