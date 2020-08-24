class __NJS_Class_Object
{
public:
	int cnt = 0;
	void Delete();
	__NJS_Class_Object();
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

class __NJS_Class_String
{
public:
	int cnt = 0;
	void Delete();
	__NJS_Class_String(string _str);
	string __NJS_VALUE;
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

class __NJS_Class_Array
{
public:
	int cnt = 0;
	void Delete();
	__NJS_Class_Array();
	vector<__NJS_VAR> __NJS_VALUE = vector<__NJS_VAR>();
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

class __NJS_Class_Function
{
public:
	int cnt = 0;
	void Delete();
	__NJS_Class_Function(void *_f);
	void *__NJS_VALUE;
	__NJS_VAR __NEW(vector<__NJS_VAR> _args);
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

class __NJS_Class_Native
{
public:
	int cnt = 0;
	void Delete();
	__NJS_Class_Native(void *_n);
	void *__NJS_VALUE;
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

union __NJS_VAL {
	int i;
	double d;
	bool b;
	__NJS_Class_String *s;
	__NJS_Class_Array *a;
	__NJS_Class_Object *o;
	__NJS_Class_Function *f;
	__NJS_Class_Native *n;
};
