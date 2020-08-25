namespace NJS::Class
{
	Object::Object()
	{
		cnt++;
	}

	void Object::Delete()
	{
		this->cnt--;
		if (this->cnt < 1)
		{
			delete this;
		}
	}
} // namespace NJS::Class