namespace NJS::Enum
{
	enum Type:uint8_t
	{
		Undefined = 0,
		Null,
		Boolean,
		Number,
		String,
		Native,
		Array,
		Object,
		Function,
	};
}