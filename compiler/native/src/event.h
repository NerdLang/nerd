#include <deque>

#ifndef __NJS_ENV_ARDUINO
	#include <chrono>
	#include <thread>
#endif

namespace NJS::Event
{
	std::deque<NJS::VAR> evQ = {};
	std::deque<std::tuple<uint64_t,bool,NJS::VAR>> timeQ = {};

	inline uint64_t getMillis()
	{
		#ifndef __NJS_ENV_ARDUINO
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		#else
			return millis();
		#endif
	}
	void sleep(uint64_t _timer)
	{
		#ifdef __NJS_ENV_ARDUINO
			delay(_timer);
		#else
			std::this_thread::sleep_for(std::chrono::milliseconds(_timer));
		#endif
	}

	void setTimer(NJS::VAR _var, int _timer, bool repeat)
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
					#ifndef __NJS_ENV_ARDUINO
						uint64_t& _t = std::get<0>(*it);
						NJS::VAR _ev = std::get<2>(*it);
						bool& _b = std::get<1>(*it);
					#else
						uint64_t _t = it->get<0>();
						NJS::VAR _ev = it->get<2>();
						bool _b = it->get<1>();
					#endif
					if(_t <= _now)
					{
						if(!_b) timeQ.erase(it);
						_ev();
						if(!_b) ((NJS::Class::Base*)_ev._ptr)->Delete();
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
					NJS::Event::sleep(min);
				}
			}

			if(evQ.size())
			{
				NJS::VAR _ev = evQ.front();
				evQ.pop_front();
				_ev();
				((NJS::Class::Base*)_ev._ptr)->Delete();
			}
		}
	}
}
