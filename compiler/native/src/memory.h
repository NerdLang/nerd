#pragma once
#include "classes.h"

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
		#ifndef NJS__REGISTER_SIZE
			#define NJS__REGISTER_SIZE 10000
		#endif
		VAL REGISTER[NJS__REGISTER_SIZE];
		int FREE[NJS__REGISTER_SIZE] = {0};

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
