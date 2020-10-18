// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//standard libraries
#include <iostream>
#include <sstream>
#include <chrono>


//header includes
#include "timer.hpp"
#include <var.hpp>


void Timer::start(clock_t timer) //in ms
{
	m_timer = timer;
	m_delay = clock();
	m_running = true;
	Beep(dzwiekGlowny, 100);
}

void Timer::stop()
{
	if (m_running)
	{
		m_timer = 0;
		Beep(dzwiekGlowny, 500);
		m_running = false;
		m_loaded = false;
	}
}

void Timer::update()
{
	if (m_running)
	{
		m_timer -= (clock() - m_delay);
		m_delay = clock();
	}
}

void Timer::beep()
{
	if(m_running)
		if (m_timer > 0)
		{
			update();
			if (m_loaded)
			{
				if (random)
				{
					if (m_timer < 300000)
					{
						Beep(dzwiekGlowny, 150);
						Beep(0, interval);
						Beep(dzwiekGlowny + 50, 150);
						Beep(0, interval);
						Beep(dzwiekGlowny + 100, 150);
						Beep(0, interval);
						m_loaded = 0;
					}
				}
				else
				{
					if (m_timer < 360000)
					{
						Beep(dzwiekGlowny, 150);
						Beep(0, interval);
						Beep(dzwiekGlowny + 50, 150);
						Beep(0, interval);
						Beep(dzwiekGlowny + 100, 150);
						Beep(0, interval);
						m_loaded = 0;
					}
				}
			}
		}
		else
		{
			Beep(dzwiekGlowny - 100, 150);
			Beep(0, interval);
			Beep(dzwiekGlowny - 50, 150);
			Beep(0, interval);
			Beep(dzwiekGlowny, 150);
			Beep(0, interval);
			mainTimer.stop();
			pos.X = 0;
			pos.Y = 2;
			SetConsoleCursorPosition(h, pos);
			SetConsoleTextAttribute(h, 204);
			std::cout << " ";
			SetConsoleTextAttribute(h, 12);
			pos.X = 1;
			pos.Y = 2;
			SetConsoleCursorPosition(h, pos);
			std::cout << " [t]Timer                     ";
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
	std::string m, s;
	//minutes
	if ((getSec() / 60) % 60 < 10)
		m = "0" + std::to_string(getSec() / 60);
	else
		m = std::to_string(getSec() / 60);

	//seconds
	if (getSec() % 60 < 10)
		s = "0" + std::to_string(getSec()%60);
	else
		s = std::to_string(getSec()%60);

	return m + ":" + s;
}