#pragma once
#ifndef __INC_NJS_CLASSES_HEADER
#include "classes.h"
#endif

namespace NJS
{
	namespace MEMORY
	{

		/*** REGISTER ***/

		#ifndef __NJS_REGISTER_SIZE
		#define __NJS_REGISTER_SIZE 1000000
		#endif

		int FREE_PTR = -1;
		int CURR_PTR = 0;
		#ifndef NJS__REGISTER_SIZE
			#define NJS__REGISTER_SIZE 10000
		#endif
		VAL REGISTER[NJS__REGISTER_SIZE];
		int FREE[NJS__REGISTER_SIZE] = {0};

		static int Get () 
		{
			if (FREE_PTR > -1)
			{
				return FREE[FREE_PTR--];
			}
			else
			{
				return CURR_PTR++;
			}
		}
		static void Release (int ptr) 
		{
			FREE[++FREE_PTR] = ptr;
		}
	} // namespace MEMORY
} // namespace NJS