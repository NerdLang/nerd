namespace NJS::Class
{
	class Object
	{
	public:
		int cnt = 0;
		void Delete();
		Object();
		vector<pair<const char *, NJS::VAR>> __OBJECT;
	};
} // namespace NJS::Class