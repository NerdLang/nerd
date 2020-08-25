namespace NJS::Class
{
	class Function
	{
	public:
		int cnt = 0;
		void Delete();
		Function(void *_f);
		void *__NJS_VALUE;
		NJS::VAR __NEW(vector<NJS::VAR> _args);
		vector<pair<const char *, NJS::VAR>> __OBJECT;
	};
} // namespace NJS::CLASS