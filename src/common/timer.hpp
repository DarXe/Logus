// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef _TIMER_INCLUDED_
#define _TIMER_INCLUDED_


//standard libraries
#include <string>
#include <ctime>


class Timer
{
private:
	clock_t m_delay;
public:
	int m_timer;
	bool m_running;
	bool m_loaded;
	bool m_beep;

	Timer();

	void start(const clock_t &timer);
	void stop(const bool &beep = true);
	void startCounter(const short &getSeconds = 0);
	void stopCounter();
	void update();
	void beep();
	

	int getMs();
	int getSec();

	std::string getTime();
};

#endif