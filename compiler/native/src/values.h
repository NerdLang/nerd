namespace NJS
{
	namespace Value
	{
		auto undefined = NJS::VAR(NJS::Enum::Type::UNDEFINED, 0);
		auto null = NJS::VAR(NJS::Enum::Type::ISNULL, 0);
		auto Infinity = NJS::VAR(NJS::Enum::Type::NUMBER, INFINITY);
		auto NaN = NJS::VAR(NJS::Enum::Type::ISNAN, 0);
	} // namespace NJS::Value
} // namespace NJS
