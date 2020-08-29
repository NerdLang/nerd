namespace NJS
{
	namespace MEMORY
	{

		/*** REGISTER ***/

		#ifndef __NJS_REGISTER_SIZE
		#define __NJS_REGISTER_SIZE 1000000
		#endif

		int FREE_PTR = -1;
		int REGISTER_PTR = 0;
		#ifdef CL_WINDOWS
		NJS::VAL REGISTER[__NJS_REGISTER_SIZE];
		#else
		NJS::VAL REGISTER[__NJS_REGISTER_SIZE]{(NJS::VAL){.i = 0}};
		#endif
		int FREE[__NJS_REGISTER_SIZE] = {0};

		/*** END REGISTER ***/
	} // namespace NJS::MEMORY
} // namespace NJS