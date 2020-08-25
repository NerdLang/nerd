namespace NJS
{
	union VAL {
		int i;
		double d;
		bool b;
		__NJS_Class_String *s;
		__NJS_Class_Array *a;
		__NJS_Class_Object *o;
		__NJS_Class_Function *f;
		__NJS_Class_Native *n;
	};
} // namespace NJS