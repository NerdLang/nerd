namespace NJS::Class
{
	class Native
	{
	public:
		int cnt = 0;
		void Delete();
		Native(void *_n);
		void *__NJS_VALUE;
		vector<pair<const char *, NJS::VAR>> __OBJECT;
	};
} // namespace NJS::Class