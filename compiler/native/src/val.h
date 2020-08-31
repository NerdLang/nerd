namespace NJS
{
	union VAL {
		NJS::Class::Number *i;
		NJS::Class::Undefined *u;
		NJS::Class::Boolean *b;
		NJS::Class::String *s;
		NJS::Class::Array *a;
		NJS::Class::Object *o;
		NJS::Class::Function *f;
		NJS::Class::Native *n;
	};
} // namespace NJS