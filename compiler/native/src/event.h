#include <deque>
#include <chrono>

#ifdef __NJS_ENV_STD
	#include <thread>
#endif

namespace NJS::Event
{
	std::deque<NJS::VAR> evQ = {};
	std::deque<std::tuple<uint64_t,bool,NJS::VAR>> timeQ = {};

	void sleep(uint64_t _timer)
	{
		#ifdef __NJS_ENV_STD
		std::this_thread::sleep_for(std::chrono::milliseconds(_timer));
		#endif
	}

	void setTimer(NJS::VAR _var, int _timer, bool repeat)
	{
		uint64_t _trigger = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
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
				uint64_t _now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
				for(auto it = timeQ.begin(); it != timeQ.end();)
				{
					if(std::get<0>(*it) <= _now)
					{
						NJS::VAR _ev = std::get<2>(*it);
						if(!std::get<1>(*it)) timeQ.erase(it);
						_ev();
						if(!std::get<1>(*it)) ((NJS::Class::Base*)_ev._ptr)->Delete();
						else it++;
					}
					else
					{
						if(std::get<0>(*it) - _now < min) min = std::get<0>(*it) - _now;
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
