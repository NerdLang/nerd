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
		explicit NJS::Class::Undefined::operator bool() const
		{
			return false;
		}
		explicit NJS::Class::Undefined::operator double() const
		{
			return 0;
		}
		explicit NJS::Class::Undefined::operator int() const
		{
			return 0;
		}
		explicit NJS::Class::Undefined::operator std::string() const
		{
			return "undefined";
		}
		explicit NJS::Class::Undefined::operator long long() const
		{
			return 0;
		}
		NJS::VAR const &operator[](std::string _index) const;
		NJS::VAR &operator[](std::string _index);
		template <class... Args>
		NJS::VAR operator()(Args... args) const;
	};
} // namespace NJS::Class
