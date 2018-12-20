#ifndef _TIMER_PROVIDER_H_
#define _TIMER_PROVIDER_H_
#include "../BaseProvider.h"
#include "Timer.h"
#include <vector>
#include "../SEVector.h"

#ifdef WINDOW_SDL2
	#include "SDLTimer.h"
#endif

class TimerProvider : public BaseProvider
{
public:
	TimerProvider() : BaseProvider()
	{
#ifdef WINDOW_SDL2
		timers_.push_back(new SDLTimer());
#endif

		activeTimer_ = timers_.at(0);
	}



	bool IsInit() override { return true; }
	std::string GetKey() override { return GetKeyStatic(); };
	static std::string GetKeyStatic() { return "Timer"; }
private:
	Timer * activeTimer_;
	std::vector<Timer*> timers_;
};

#endif