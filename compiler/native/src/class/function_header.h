namespace NJS::Class
{
	class Function
	{
	public:
		int cnt = 0;
		string code = "[native code]";
		void Delete();
		Function(void *_f);
		void *__NJS_VALUE;
		vector<pair<const char *, NJS::VAR>> __OBJECT;
		
		NJS::VAR Call(var __INJECTED_THIS, vector<var> __NJS_VARARGS);
		
		template <class... Args>
		NJS::VAR operator()(Args... args);
		
		explicit operator std::string() const
		{
			return code;
		}
	};
} // namespace NJS::CLASS