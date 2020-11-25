/*
 * This file is part of NectarCPP
 * Copyright (c) 2020 - 2020 Adrien THIERRY
 * https://nectar-lang.org - https://seraum.com/
 *
 * sources : https://github.com/nectar-lang/NectarCPP
 * 
 * NectarCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarCPP.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#include <deque>

namespace NectarCore::Event
{
	std::deque<NectarCore::VAR> evQ = {};
	std::deque<std::tuple<uint64_t,bool,NectarCore::VAR>> timeQ = {};

	inline uint64_t getMillis()
	{
		#ifndef __Nectar_ENV_ARDUINO
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		#else
			return millis();
		#endif
	}
	void sleep(uint64_t _timer)
	{
		#ifdef __Nectar_ENV_ARDUINO
			delay(_timer);
		#else
			std::this_thread::sleep_for(std::chrono::milliseconds(_timer));
		#endif
	}

	void setTimer(NectarCore::VAR _var, int _timer, bool repeat)
	{
		uint64_t _trigger = getMillis();
		_trigger += _timer;
		timeQ.push_back({_trigger, repeat, _var});
	}

	void Loop()
	{
		while(evQ.size() || timeQ.size())
		{
			if(timeQ.size())
			{
				uint64_t min = 1000;
				uint64_t _now = getMillis();
				for(auto it = timeQ.begin(); it != timeQ.end();)
				{
					#ifndef __Nectar_ENV_ARDUINO
						uint64_t& _t = std::get<0>(*it);
						NectarCore::VAR _ev = std::get<2>(*it);
						bool& _b = std::get<1>(*it);
					#else
						uint64_t _t = it->get<0>();
						NectarCore::VAR _ev = it->get<2>();
						bool _b = it->get<1>();
					#endif
					if(_t <= _now)
					{
						if(!_b) timeQ.erase(it);
						_ev();
						if(!_b) ((NectarCore::Class::Base*)_ev.data.ptr)->Delete();
						else it++;
					}
					else
					{
						if(_t - _now < min) min = _t - _now;
						it++;
					}
				}
				if(evQ.size() == 0 && timeQ.size() > 0)
				{
					NectarCore::Event::sleep(min);
				}
			}

			if(evQ.size())
			{
				NectarCore::VAR _ev = evQ.front();
				evQ.pop_front();
				_ev();
				((NectarCore::Class::Base*)_ev.data.ptr)->Delete();
			}
		}
	}
}
