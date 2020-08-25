namespace NJS
{
	namespace MEMORY
	{

		/*** REGISTER ***/

		#ifndef __NJS_REGISTER_SIZE
		#define __NJS_REGISTER_SIZE 100000
		#endif

		int FREE_PTR = -1;
		int REGISTER_PTR = 0;
		#ifdef CL_WINDOWS
		__NJS_VAL REGISTER[__NJS_REGISTER_SIZE];
		#else
		__NJS_VAL REGISTER[__NJS_REGISTER_SIZE]{(__NJS_VAL){.i = 0}};
		#endif
		int FREE[__NJS_REGISTER_SIZE] = {0};

		/*** END REGISTER ***/
	} // namespace NJS::MEMORY
} // namespace NJS