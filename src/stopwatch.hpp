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
	long double get(std::string type);

	std::string pre(std::string type, int precision = 0);

	void debugOutput(std::string text, std::vector <std::string> content);
};