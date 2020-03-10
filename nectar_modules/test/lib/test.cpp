// FFI example
#ifdef _WIN32
    #include "windows.h"
#endif

var __FFI_TEST()
{
	#ifdef _WIN32
	int msgboxID = MessageBox(NULL, "Are you Ok?", "Ok ?", MB_ICONWARNING | MB_YESNOCANCEL);
	#else 
	 cout << "this platform is not compatible with MessageBox" << "\n";
	#endif
	cout << "test" << "\n";
	return var("Return FFI");
}
