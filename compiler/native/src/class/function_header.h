#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Function : public virtual Base
	{
	public:
		// Constructors
		Function();
		Function(void* val);
		Function(void* val, NJS::VAR bind);
		// Properties
		count_t counter = 0;
		#ifdef __NJS_DEBUG
		std::string code = "[native code]";
		#endif
		NJS::Type::function_t* value = nullptr;
		var This;
		NJS::Type::object_t object;
		// Methods
		inline void Delete() noexcept;
		inline void jsDelete(std::string _key) noexcept;
		inline void* Copy() noexcept;
		
		NJS::VAR Call(var& __NJS_THIS, NJS::VAR* __NJS_VARARGS, int __NJS_VARLENGTH);
		
		template <class... Args>
		NJS::VAR New(Args... args);
		// Native cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		NJS::VAR const operator[](NJS::VAR key) const;
		NJS::VAR &operator[](NJS::VAR key);
		template <class... Args> NJS::VAR operator()(Args... args);
		// Comparation operators
		Function operator!() const;
		bool operator==(const Function &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const Function &_v1) const;
		bool operator<(const Function &_v1) const;
		bool operator<=(const Function &_v1) const;
		bool operator>(const Function &_v1) const;
		bool operator>=(const Function &_v1) const;
		// Numeric operators
		Function operator+() const;
		Function operator-() const;
		Function operator++(const int _v1);
		Function operator--(const int _v1);
		Function operator+(const Function &_v1) const;
		Function operator+=(const Function &_v1);
		Function operator-(const Function &_v1) const;
		Function operator-=(const Function &_v1);
		Function operator*(const Function &_v1) const;
		Function operator*=(const Function &_v1);
		// TODO: "**" and "**=" operators
		Function operator/(const Function &_v1) const;
		Function operator/=(const Function &_v1);
		Function operator%(const Function &_v1) const;
		Function operator%=(const Function &_v1);
		Function operator&(const Function &_v1) const;
		Function operator|(const Function &_v1) const;
		Function operator^(const Function &_v1) const;
		Function operator~() const;
		Function operator>>(const Function &_v1) const;
		Function operator<<(const Function &_v1) const;
		Function operator&=(const Function &_v1);
		Function operator|=(const Function &_v1);
		Function operator^=(const Function &_v1);
		Function operator>>=(const Function &_v1);
		Function operator<<=(const Function &_v1);
		// TODO: ">>>" and ">>>=" operators
		NJS::VAR toString(NJS::VAR* _args, int _length) const;
		NJS::VAR valueOf(NJS::VAR* _args, int _length) const;
		NJS::VAR bind(NJS::VAR* _args, int _length);
		NJS::VAR call(NJS::VAR* _args, int _length);
		NJS::VAR apply(NJS::VAR* _args, int _length);
	};
} // namespace NJS::Class
