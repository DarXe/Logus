// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <chrono>
#include <string>
#include <vector>


class Stopwatch
{
	std::chrono::high_resolution_clock::time_point m_start, m_stop;
	long double m_time;
public:
	Stopwatch();
	~Stopwatch();

	void stop();
	long double get(const std::string &type);

	std::string pre(const std::string &type, const int &precision = 0);
};