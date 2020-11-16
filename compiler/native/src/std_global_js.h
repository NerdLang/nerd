
NJS::VAR setImmediate = __NJS_Create_Var_Unscoped_Anon(
	NJS::VAR _fn;
	if (__NJS_VARLENGTH > 0) _fn = __NJS_VARARGS[0];
	NJS::Event::evQ.push_back(_fn);
	return NJS::Global::undefined;	
);

NJS::VAR setTimeout = __NJS_Create_Var_Unscoped_Anon(
	NJS::VAR _fn;
	NJS::VAR _delay;
	if (__NJS_VARLENGTH > 0) _fn = __NJS_VARARGS[0];
	if (__NJS_VARLENGTH > 1) _delay = __NJS_VARARGS[1];
	
	NJS::Event::setTimer(_fn, (int)_delay, false);
	
	return NJS::Global::undefined;
);

NJS::VAR setInterval = __NJS_Create_Var_Unscoped_Anon(
	NJS::VAR _fn;
	NJS::VAR _delay;
	if (__NJS_VARLENGTH > 0) _fn = __NJS_VARARGS[0];
	if (__NJS_VARLENGTH > 1) _delay = __NJS_VARARGS[1];
	
	NJS::Event::setTimer(_fn, (int)_delay, true);
	
	return NJS::Global::undefined;
);
