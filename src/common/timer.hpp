// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef _TIMER_INCLUDED_
#define _TIMER_INCLUDED_


//standard libraries
#include <string>


class Timer
{
private:
	clock_t m_delay;
public:
	int m_timer = 0;
	bool m_running = 0;
	bool m_loaded = 0;
	bool m_beep = 0;

	void start(clock_t delay);
	void stop(const bool &beep = true);
	void startCounter(short getSeconds = 0);
	void stopCounter();
	void update();
	void beep();
	

	int getMs();
	int getSec();

	std::string getTime();
};

#endif