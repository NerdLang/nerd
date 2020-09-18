namespace NJS
{
	typedef std::vector<NJS::VAR> vector_t;
	typedef std::vector<void*> vector_p;
	typedef std::pair<const char *, NJS::VAR> pair_t;
	typedef std::vector<pair_t> object_t;
	const int SMI_MAX = 1073741823;
	const int SMI_MIN = -1073741824;
}