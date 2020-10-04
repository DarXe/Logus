// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//standard libraries
#include <iostream>
#include <sstream>
#include <chrono>


//header includes
#include "timer.hpp"


Timer::Timer(int timer)
{
	start(timer);
}

inline void Timer::start(clock_t timer) //in ms
{
	m_timer = timer;
	m_delay = clock();
	m_running = true;
}

void Timer::stop()
{
	if (m_running)
	{
		m_timer = 0;
		m_running = false;
	}
}

void Timer::update()
{
	if (m_running)
	{
		m_timer -= (clock() - m_delay);
	}
}

int Timer::getMs()
{
	return m_timer;
}

int Timer::getSec()
{
	return m_timer / 1000;
}

std::string Timer::getTime()
{
	const int time = 60;
	std::string m, s;
	//minutes
	if ((time / 60) % 60 < 10)
		m = "0" + std::to_string(time / 60);
	else
		m = std::to_string(time / 60);

	//seconds
	if (time % 60 < 10)
		s = "0" + std::to_string(time%60);
	else
		m = std::to_string(time%60);

	return m + ":" + s;
}