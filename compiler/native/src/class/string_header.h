namespace NJS::Class
{
	class String
	{
	public:
		int cnt = 0;
		void Delete();
		String(string _str);
		string __NJS_VALUE;
		vector<pair<const char *, NJS::VAR>> __OBJECT;
	};
}