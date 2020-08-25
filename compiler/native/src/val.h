namespace NJS
{
	union VAL {
		int i;
		double d;
		bool b;
		NJS::Class::String *s;
		NJS::Class::Array *a;
		NJS::Class::Object *o;
		NJS::Class::Function *f;
		NJS::Class::Native *n;
	};
} // namespace NJS