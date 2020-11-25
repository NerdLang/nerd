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

std::unordered_map<std::string, std::mutex> __Nectar_Thread_mutexList;
std::vector<std::thread> __Nectar_Thread_List;

void __Nectar_THREADED_CALL(NectarCore::VAR _fn)
{
	try
	{
		_fn();
	}
	catch(NectarCore::VAR e)
	{
		__Nectar_Log_Console(e);
	}
}
 
function __Nectar_NATIVE_THREAD_RUN(_cb)
{
	if(_cb)
	{
		__Nectar_Thread_List.emplace_back(__Nectar_THREADED_CALL, _cb);
	}
};

function __Nectar_NATIVE_LOCK_GUARD(_key)
{
	if(!_key) _key = "default";
	std::lock_guard<std::mutex> guard(__Nectar_Thread_mutexList[(std::string)_key]);
};

function __Nectar_NATIVE_WAIT_FOR_ALL()
{
	for(auto& _thread: __Nectar_Thread_List)
	{
		_thread.join();
	}
};

