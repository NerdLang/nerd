#ifdef __NJS__OBJECT_HASHMAP
#include <unordered_map>
#endif
namespace NJS
{
	namespace Type
	{
		typedef std::vector<NJS::VAR> vector_t;
		typedef std::vector<void*> vector_p;
		typedef std::pair<std::string, NJS::VAR> pair_t;
		#ifdef __NJS__OBJECT_HASHMAP
		typedef std::unordered_map<std::string, NJS::VAR> object_t;
		#else
		typedef std::vector<pair_t> object_t;
		#endif
		typedef std::function<NJS::VAR (VAR&, VAR*, int)> function_t;
	}
}