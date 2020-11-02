namespace NJS::Enum
{
	enum Type:uint8_t
	{
		ISNAN = 0,
		ISINFINITY,
		ISNULL,
		Undefined,
		Boolean,
		Number,
		String,
		Native,
		Array,
		Object,
		Function,
	};
}