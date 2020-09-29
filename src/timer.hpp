// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef _TIMER_INCLUDED_
#define _TIMER_INCLUDED_


//standard libraries
#include <chrono>
#include <string>


class Timer
{
private:
	bool m_running;
	int m_timer;
	clock_t m_delay;
public:
	Timer(int timer);

	void start(clock_t delay);
	void stop();
	void update();

	int getMs();
	int getSec();

	std::string getTime();
};

#endif