namespace NJS::Class
{
	class Array
	{
	public:
		int cnt = 0;
		void Delete();
		Array();
		vector<NJS::VAR> __NJS_VALUE = vector<NJS::VAR>();
		vector<pair<const char *, NJS::VAR>> __OBJECT;
		NJS::VAR __iterator(std::vector<NJS::VAR> __NJS_VARARGS) const;
		NJS::VAR __unscopables(std::vector<NJS::VAR> __NJS_VARARGS) const;
		NJS::VAR join(std::vector<NJS::VAR> args) const;
		NJS::VAR toString(std::vector<NJS::VAR> __NJS_VARARGS) const;
	};
} // namespace NJS::Class