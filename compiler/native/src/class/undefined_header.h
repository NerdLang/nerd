namespace NJS::Class
{
	class Undefined
	{
	public:
		const char *name = "undefined";
		const NJS::Enum::Type type = NJS::Enum::Type::UNDEFINED;
		unsigned int cnt = 0;
		Undefined();
		void Delete();
		explicit operator bool() const
		{
			return false;
		}
		explicit operator double() const
		{
			return 0;
		}
		explicit operator int() const
		{
			return 0;
		}
		explicit operator std::string() const
		{
			return "undefined";
		}
		explicit operator long long() const
		{
			return 0;
		}
		NJS::VAR const &operator[](std::string _index) const;
		NJS::VAR &operator[](std::string _index);
		template <class... Args>
		NJS::VAR operator()(Args... args) const;
	};
} // namespace NJS::Class
