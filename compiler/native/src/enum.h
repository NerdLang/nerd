namespace NJS::Enum
{
	enum Type:uint8_t
	{
		Undefined = 1,
		Number,
		Object,
		Boolean,
		String,
		Native,
		Function,
		Array,
		ISNAN,
		ISINFINITY,
		ISNULL,
	};
}