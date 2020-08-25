namespace NJS::Class
{
	Array::Array()
	{
		cnt++;
		
		__NJS_CreateMethodToClass("@@iterator", __iterator);
		__NJS_CreateMethodToClass("@@unscopables", __unscopables);
		__NJS_CreateMethodToClass("concat", concat);
		__NJS_CreateMethodToClass("copyWithin", copyWithin);
		__NJS_CreateMethodToClass("entries", entries);
		__NJS_CreateMethodToClass("every", every);
		__NJS_CreateMethodToClass("fill", fill);
		__NJS_CreateMethodToClass("filter", filter);
		__NJS_CreateMethodToClass("find", find);
		__NJS_CreateMethodToClass("findIndex", findIndex);
		__NJS_CreateMethodToClass("flat", flat);
		__NJS_CreateMethodToClass("flatMap", flatMap);
		__NJS_CreateMethodToClass("forEach", forEach);
		__NJS_CreateMethodToClass("includes", includes);
		__NJS_CreateMethodToClass("indexOf", indexOf);
		__NJS_CreateMethodToClass("join", join);
		__NJS_CreateMethodToClass("keys", keys);
		__NJS_CreateMethodToClass("lastIndexOf", lastIndexOf);
		__NJS_CreateMethodToClass("map", map);
		__NJS_CreateMethodToClass("pop", pop);
		__NJS_CreateMethodToClass("push", push);
		__NJS_CreateMethodToClass("reduce", reduce);
		__NJS_CreateMethodToClass("reduceRight", reduceRight);
		__NJS_CreateMethodToClass("reverse", reverse);
		__NJS_CreateMethodToClass("shift", shift);
		__NJS_CreateMethodToClass("slice", slice);
		__NJS_CreateMethodToClass("some", some);
		__NJS_CreateMethodToClass("sort", sort);
		__NJS_CreateMethodToClass("splice", splice);
		__NJS_CreateMethodToClass("toLocaleString", toLocaleString);
		__NJS_CreateMethodToClass("toString", toString);
		__NJS_CreateMethodToClass("unshift", unshift);
		__NJS_CreateMethodToClass("values", values);
		
		__NJS_Object_Set("length", 0, &this->__OBJECT);

	}

	Array::Array(std::vector<NJS::VAR> vec)
	{
		Array::Array();
		__NJS_VALUE = vec;
		__NJS_Object_Set("length", (int)vec.size(), &this->__OBJECT);
	}
		
	void Array::Delete()
	{
		this->cnt--;
		if (this->cnt < 1)
		{
			delete this;
		}
	}
	
	NJS::VAR NJS::Class::Array::__iterator(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::__unscopables(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::concat(std::vector<NJS::VAR> args) const
	{
		/*
		auto &res = *new NJS::Class::Array();
		auto &vec = res.__NJS_VALUE;
		for (auto _arr : args)
		{
			auto &arr = (NJS::Class::Array)_arr;
			vec.insert(vec.end(), arr.begin(), arr.end());
		}
		return res;
		*/
		return NJS::VAR();
	}
	NJS::VAR NJS::Class::Array::copyWithin(std::vector<NJS::VAR> args)
	{
		/*
		auto &vec = __NJS_VALUE;
		int _size = args.size();
		int target = _size > 0 ? (int)args[0] : 0;
		int start = _size > 1 ? (int)args[1] : 0;
		int end = _size > 2 ? (int)args[2] : vec.size();
		int size = vec.size();
		if (start < 0)
		{
			start += size;
		}
		if (end < 0)
		{
			end += size;
		}
		std::copy(vec.begin() + target, vec.begin() + end, vec.begin() + start);
		return *this;*/
		return NJS::VAR();
	}
	NJS::VAR NJS::Class::Array::entries(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::every(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::fill(std::vector<NJS::VAR> args) const
	{
		/*
		NJS::VAR value = args.size() ? args[0] : NJS::Value::undefined;
		__NJS_VALUE.assign(__NJS_VALUE.size(), value);
		return *this;
		*/
		return NJS::VAR();
	};
	NJS::VAR NJS::Class::Array::filter(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::find(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::findIndex(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::flat(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::flatMap(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::forEach(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::includes(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::indexOf(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::join(std::vector<NJS::VAR> args) const
	{
		auto _str = (std::string)(args.size() ? args[0] : NJS::Value::undefined);
		int l = __NJS_VALUE.size();
		if (l == 0)
			return "";
		std::stringstream stream;
		stream << (std::string)__NJS_VALUE[0];
		for (int i = 1; i < l; i++)
		{
			stream << _str << (std::string)__NJS_VALUE[i];
		}
		return stream.str();
	};
	NJS::VAR NJS::Class::Array::keys(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::lastIndexOf(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::map(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::pop(std::vector<NJS::VAR> args) {}
	NJS::VAR NJS::Class::Array::push(std::vector<NJS::VAR> args)
	{
		for (auto value : args)
		{
			__NJS_VALUE.push_back(value);
		}
		__NJS_Object_Set("length", (int)__NJS_VALUE.size(), &this->__OBJECT);
		return this;
	};
	NJS::VAR NJS::Class::Array::reduce(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::reduceRight(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::reverse(std::vector<NJS::VAR> args) {
		std::reverse(__NJS_VALUE.begin(), __NJS_VALUE.end());
		return this;
	}
	NJS::VAR NJS::Class::Array::shift(std::vector<NJS::VAR> args) {}
	NJS::VAR NJS::Class::Array::slice(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::some(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::sort(std::vector<NJS::VAR> args) const {}
	NJS::VAR NJS::Class::Array::splice(std::vector<NJS::VAR> args) {}
	NJS::VAR NJS::Class::Array::toLocaleString(std::vector<NJS::VAR> args) const
	{
		int l = __NJS_VALUE.size();
		if (l == 0)
			return "";
		std::stringstream stream;
		stream << (std::string)__NJS_VALUE[0]["toLocaleString"]();
		for (int i = 1; i < l; i++)
		{
			NJS::VAR val = __NJS_VALUE[i];
			stream << "," << (std::string)val["toLocaleString"]();
		}
		return stream.str();
	}
	NJS::VAR NJS::Class::Array::toString(std::vector<NJS::VAR> args) const
	{
		return join(std::vector<NJS::VAR>({","}));
	}

	NJS::VAR NJS::Class::Array::unshift(std::vector<NJS::VAR> values)
	{
		auto pos = __NJS_VALUE.begin();
		for (auto value : values)
		{
			__NJS_VALUE.insert(pos, value);
		}
		return this;
	}
	NJS::VAR NJS::Class::Array::values(std::vector<NJS::VAR> args) const {}
}