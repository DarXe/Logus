// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef _STOPWATCH_INCLUDED_
#define _STOPWATCH_INCLUDED_


//standard libraries
#include <string>
#include <chrono>


enum unit
{
	s,
	ms,
	ns
};

class Stopwatch
{
public:
	Stopwatch();
	~Stopwatch();

	void stop();
	long double get(const unit &u);

	std::string pre(const unit &u, const int &precision = 0);
private:
	std::chrono::high_resolution_clock::time_point m_start, m_stop;
	long double m_time;
};

#endif