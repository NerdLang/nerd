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
	};
} // namespace NJS::Class