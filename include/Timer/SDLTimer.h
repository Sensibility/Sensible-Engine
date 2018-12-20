#ifndef _SDL_TIMER_H_
#define _SDL_TIMER_H_
#include "Timer.h"
#include "sdl2/SDL_stdinc.h"
#include "../Renderer/SDL.h"

class SDLTimer: public Timer
{
public:
	SDLTimer() : Timer()
	{
		start_ = 0;
		stop_ = 0;
	}
	void Start() override
	{
		start_ = SDL_GetTicks();
	};
	void Stop() override
	{
		stop_ = SDL_GetTicks();
	};
	void Restart() override
	{
		Start();
	};
	double Elapsed() override
	{
		return (double)(stop_ - start_) / 1000;
	};
private:
	Uint32 start_, stop_;
	
};

#endif