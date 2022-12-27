/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/

NerdCore::VAR __NERD_delete(NerdCore::VAR _left, NerdCore::VAR _right);
NerdCore::VAR __NERD_Object_Set(std::string _index, NerdCore::VAR _value, NerdCore::Type::object_t *_obj);
NerdCore::VAR __NERD_Object_Set(NerdCore::VAR _index, NerdCore::VAR _value, NerdCore::VAR _array);
std::string type_of(NerdCore::Global::var _var);
std::string typeof(NerdCore::Global::var _var);


/*
inline NerdCore::Global::var Object()
{
	return NerdCore::VAR((NerdCore::Class::Object *)new NerdCore::Class::Object());
}
*/
/*
inline NerdCore::Global::var Object(NerdCore::Type::object_t _obj)
{
	return new NerdCore::Class::Object(_obj);
}
*/

inline NerdCore::Global::var Array()
{
	return new NerdCore::Class::Array();
}

inline NerdCore::Global::var FixedArray()
{
	return new NerdCore::Class::FixedArray();
}

inline NerdCore::Global::var FixedArray(NerdCore::Global::var _length)
{
	return new NerdCore::Class::FixedArray(_length);
}

inline NerdCore::Global::var FixedArray(int _length)
{
	return new NerdCore::Class::FixedArray(_length);
}