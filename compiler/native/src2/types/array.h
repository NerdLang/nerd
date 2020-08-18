#include <vector>
#include <base.h>

using namespace NJS;

class NJS::CLASS::Array : public CLASS::BaseObject {
	public:
		VAR Array()
		{
			cnt++;
			this["toString"] = __NJS_VAR(__NJS_FUNCTION, VAR new function<VAR()>([&]() {
				return "Array";
			}))

			function<__NJS_VAR(vector<var>)> *__NJS_ARRAY_PUSH = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
				var _add;
				if (__NJS_VARARGS.size() > 0)
					_add = __NJS_VARARGS[0];
				else
					return (int)this->__NJS_VALUE.size();

				this->__NJS_VALUE.push_back(_add);
				__NJS_Object_Set("length", (int)this->__NJS_VALUE.size(), &this->__OBJECT);

				return (int)this->__NJS_VALUE.size();
			});
			__NJS_VAR arrayPush = __NJS_VAR(__NJS_FUNCTION, __NJS_ARRAY_PUSH);
			__NJS_Object_Set("push", arrayPush, &this->__OBJECT);

			__NJS_Object_Set("length", 0, &this->__OBJECT);
		}
		vector<VAR> __NJS_VALUE = vector<VAR>();
};

