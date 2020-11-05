/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

std::unordered_map<std::string, std::mutex> __NJS_Thread_mutexList;

void __NJS_THREADED_CALL(NJS::VAR _fn)
{
    _fn();
}
 
function __NJS_NATIVE_THREAD_RUN(_cb)
{
	if(_cb)
	{
		std::thread _thread(&__NJS_THREADED_CALL, _cb);
		_thread.join();
	}
};

function __NJS_NATIVE_LOCK_GUARD(_key)
{
	if(!_key) _key = "default";
	std::lock_guard<std::mutex> guard(__NJS_Thread_mutexList[(std::string)_key]);
};

