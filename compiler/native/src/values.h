namespace NJS::Global
{	
	using var = NJS::VAR;
	using let = NJS::VAR;
	auto undefined = NJS::VAR(new NJS::Class::Undefined());
	NJS::VAR null = __NJS_Create_Null();
	NJS::VAR Infinity = std::numeric_limits<double>::infinity();
	NJS::VAR NaN = std::numeric_limits<double>::quiet_NaN();
	
	NJS::VAR __NJS_InitVar()
	{
		return NJS::VAR();
	}
	
	template <typename T>
	NJS::VAR __NJS_InitVar(T _init)
	{
		return NJS::VAR(_init);
	}
}