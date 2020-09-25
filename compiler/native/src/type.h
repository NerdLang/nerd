namespace NJS
{
	namespace Type
	{
		typedef std::vector<NJS::VAR> vector_t;
		typedef std::vector<void*> vector_p;
		typedef std::pair<std::string, NJS::VAR> pair_t;
		typedef std::vector<pair_t> object_t;
		typedef std::function<NJS::VAR (VAR, NJS::Type::vector_t)> function_t;
	}
}