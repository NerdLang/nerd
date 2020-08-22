#include "function.h"
#include "object.cpp"
#include <limits>

NJS::Class::Function::Function(void *_f)
{
	Object();
	NJS::VAR proto = NJS::Class::Object();
	(*this)["prototype"] = proto;
	__NJS_VALUE = _f;
}

explicit NJS::Class::Function::operator std::string() const
{
	return "function () { [native code] }";
}

template <class... Args>
NJS::VAR NJS::Class::Function::operator()(Args... args) const
{
	vector<NJS::VAR> _args = vector<var>{(NJS::VAR)args...};
	return (*static_cast<function<NJS::VAR(vector<NJS::VAR>)> *>(__NJS_VALUE))(_args);
}
