#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
public:
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Restart() = 0;
	virtual double Elapsed() = 0;
};

#endif