namespace NJS::Class
{
	Native::Native(void *_n)
	{
		cnt++;
		__NJS_VALUE = _n;
	}

	void Native::Delete()
	{
		this->cnt--;
		if (this->cnt < 1)
		{
			delete this;
		}
	}
} // namespace NJS::Class