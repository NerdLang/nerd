namespace NJS
{
	union VAL {
		int i;
		double d;
		NJS::Class::Boolean *b;
		NJS::Class::String *s;
		NJS::Class::Array *a;
		NJS::Class::Object *o;
		NJS::Class::Function *f;
		NJS::Class::Native *n;
	};
} // namespace NJS