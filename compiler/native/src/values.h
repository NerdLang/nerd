	
	auto undefined = NJS::VAR();
	auto null = NJS::VAR(NJS::Enum::Type::ISNULL, 0);
	auto Infinity = NJS::VAR(std::numeric_limits<double>::infinity());
	auto NaN = NJS::VAR(NJS::Enum::Type::ISNAN, 0);

