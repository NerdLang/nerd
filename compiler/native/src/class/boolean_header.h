namespace NJS::Class
{
	class Boolean : public Object
	{
	public:
		const char *name = "boolean";
		const NJS::Enum::Type type = NJS::Enum::Type::BOOLEAN;
		Boolean();
		Boolean(bool b);
		bool __NJS_VALUE;
		explicit operator bool() const
		{
			return __NJS_VALUE;
		}
		explicit operator double() const
		{
			return __NJS_VALUE;
		}
		explicit operator int() const
		{
			return __NJS_VALUE;
		}
		explicit operator std::string() const
		{
			return __NJS_VALUE ? "true" : "false";
		}
		explicit operator long long() const
		{
			return __NJS_VALUE;
		}
		Boolean operator=(const Boolean &_v);
		Boolean operator=(const bool &_v);
	};
} // namespace NJS::Class
