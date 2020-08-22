#pragma once

namespace NJS {
	namespace Func {
		void eval(NJS::VAR str);
		bool EqualStrict(NJS::VAR a, NJS::VAR b);
		bool NotEqualStrict(NJS::VAR a, NJS::VAR b);
	};
}
