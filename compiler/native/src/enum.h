namespace NJS::Enum
{
	enum Type:uint8_t
	{
		ISNAN = 0,
		ISINFINITY,
		ISNULL,
		Undefined,
		Number,
		Boolean,
		String,
		Native,
		Array,
		Object,
		Function,
	};
}