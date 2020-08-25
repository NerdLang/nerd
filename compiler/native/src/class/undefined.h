namespace NJS::Class
{
	Undefined::Undefined()
	{
		this->cnt++;
	}

	void Undefined::Delete()
	{
		this->cnt--;
		if (this->cnt == 0)
		{
			delete this;
		}
	}

	const NJS::VAR &Undefined::operator[](std::string _index) const
	{
		throw NJS::VAR("TypeError: Cannot read property '" + _index + "' of " + (std::string) * this);
	}

	NJS::VAR &Undefined::operator[](std::string _index)
	{
		throw NJS::VAR("TypeError: Cannot read property '" + _index + "' of " + (std::string) * this);
	}

	template <class... Args>
	NJS::VAR Undefined::operator()(Args... args) const
	{
		throw NJS::VAR("TypeError: " + (std::string) * this + " is not a function");
	}
}