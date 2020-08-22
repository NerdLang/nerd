#pragma once
#include "classes.h"

#ifdef IDE_INDEV
#define NJS__REGISTER_SIZE 10000
#else
#define NJS__REGISTER_SIZE {{REGISTER}}
#endif

namespace NJS
{
	namespace MEMORY
	{
		union VAL {
			NJS::Class::Array *a;
			NJS::Class::Boolean *b;
			NJS::Class::Function *f;
			NJS::Class::Native *n;
			NJS::Class::Number *i;
			NJS::Class::Object *o;
			NJS::Class::String *s;
			NJS::Class::Undefined u;
		};
		int FREE_PTR = -1;
		int CURR_PTR = 0;
		const unsigned int SIZE = NJS__REGISTER_SIZE;
		VAL REGISTER[SIZE]{(VAL){.i = 0}};
		int FREE[SIZE] = {0};

		static int get () {
			if (FREE_PTR > -1)
			{
				return FREE[FREE_PTR--];
			}
			else
			{
				return CURR_PTR++;
			}
		}
		static void release (int ptr) {
			FREE[++FREE_PTR] = ptr;
		}
	} // namespace MEMORY
} // namespace NJS
