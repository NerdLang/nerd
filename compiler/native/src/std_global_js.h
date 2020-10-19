
NJS::VAR setImmediate = __NJS_Create_Var_Unscoped_Anon(
	var _fn;
	if (__NJS_VARLENGTH > 0) _fn = __NJS_VARARGS[0];
	return NJS::Class::Function::Async(_fn);
);

NJS::VAR setTimeout = __NJS_Create_Var_Unscoped_Anon(
	var _fn;
	var _delay;
	if (__NJS_VARLENGTH > 0) _fn = __NJS_VARARGS[0];
	if (__NJS_VARLENGTH > 1) _delay = __NJS_VARARGS[0];
	NJS::VAR _delayed = __NJS_Create_Var_Scoped_Anon(
		std::this_thread::sleep_for (std::chrono::milliseconds((int)_delay));
		return _fn();
	);
	return NJS::Class::Function::Async(_delayed);
);