// FFI example
#if defined(_WIN32) || defined(__CYGWIN__)
    #include "windows.h"
#endif

var __FFI_SIMPLE_MSGBOX()
{
	#if defined(_WIN32) || defined(__CYGWIN__)
		int msgboxID = MessageBox(NULL, "A simple messagebox", "Nectar FFI", MB_YESNOCANCEL);
	#else 
		cout << "this platform is not compatible with MessageBox" << "\n";
	#endif
	return __NJS_VAR();
};

__NJS_FFI_FUNCTION(__WIN_MESSAGE_BOX, __NJS_VAR _message, __NJS_VAR _title)
{
	#if defined(_WIN32) || defined(__CYGWIN__)
		int msgboxID = MessageBox(NULL, __NJS_GET_STRING(_message), __NJS_GET_STRING(_title), MB_ICONWARNING | MB_YESNOCANCEL);
	#else 
		cout << "this platform is not compatible with MessageBox" << "\n";
	#endif
	return __NJS_VAR();
};
