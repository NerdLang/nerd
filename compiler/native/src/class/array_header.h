namespace NJS::Class
{
	class Array
	{
	public:
		int cnt = 0;
		void Delete();
		Array();
		Array(std::vector<NJS::VAR> vec);
		Array(NJS::VAR _var);
		vector<NJS::VAR> __NJS_VALUE = vector<NJS::VAR>();
		vector<pair<const char *, NJS::VAR>> __OBJECT;
		NJS::VAR __iterator(std::vector<NJS::VAR> args) const;
		NJS::VAR __unscopables(std::vector<NJS::VAR> args) const;
		NJS::VAR concat(std::vector<NJS::VAR> args) const;
		NJS::VAR copyWithin(std::vector<NJS::VAR> args);
		NJS::VAR entries(std::vector<NJS::VAR> args) const;
		NJS::VAR every(std::vector<NJS::VAR> args) const;
		NJS::VAR fill(std::vector<NJS::VAR> args) const;
		NJS::VAR filter(std::vector<NJS::VAR> args) const;
		NJS::VAR find(std::vector<NJS::VAR> args) const;
		NJS::VAR findIndex(std::vector<NJS::VAR> args) const;
		NJS::VAR flat(std::vector<NJS::VAR> args) const;
		NJS::VAR flatMap(std::vector<NJS::VAR> args) const;
		NJS::VAR forEach(std::vector<NJS::VAR> args) const;
		NJS::VAR includes(std::vector<NJS::VAR> args) const;
		NJS::VAR indexOf(std::vector<NJS::VAR> args) const;
		NJS::VAR join(std::vector<NJS::VAR> args) const;
		NJS::VAR keys(std::vector<NJS::VAR> args) const;
		NJS::VAR lastIndexOf(std::vector<NJS::VAR> args) const;
		NJS::VAR map(std::vector<NJS::VAR> args) const;
		NJS::VAR pop(std::vector<NJS::VAR> args);
		NJS::VAR push(std::vector<NJS::VAR> args);
		NJS::VAR reduce(std::vector<NJS::VAR> args) const;
		NJS::VAR reduceRight(std::vector<NJS::VAR> args) const;
		NJS::VAR reverse(std::vector<NJS::VAR> args);
		NJS::VAR shift(std::vector<NJS::VAR> args);
		NJS::VAR slice(std::vector<NJS::VAR> args) const;
		NJS::VAR some(std::vector<NJS::VAR> args) const;
		NJS::VAR sort(std::vector<NJS::VAR> args) const;
		NJS::VAR splice(std::vector<NJS::VAR> args);
		NJS::VAR toLocaleString(std::vector<NJS::VAR> args) const;
		NJS::VAR toString(std::vector<NJS::VAR> args) const;
		NJS::VAR unshift(std::vector<NJS::VAR> values);
		NJS::VAR values(std::vector<NJS::VAR> args) const;
	};
} // namespace NJS::Class