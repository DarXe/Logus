// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//header includes
#include "stopwatch.hpp"
#include "common.hpp"

Stopwatch::Stopwatch()
	: m_start(std::chrono::high_resolution_clock::now()), m_time(0) {}

Stopwatch::~Stopwatch()
{
	m_stop = std::chrono::high_resolution_clock::now();
	m_time = std::chrono::duration<long double, std::nano>(m_stop - m_start).count();
}

void Stopwatch::stop()
{
	m_stop = std::chrono::high_resolution_clock::now();
	m_time = std::chrono::duration<long double, std::nano>(m_stop - m_start).count();
}

long double Stopwatch::get(const unit &u)
{
	if (u == s)
		return std::chrono::duration<long double>(m_stop - m_start).count();
	else if (u == ms)
		return std::chrono::duration<long double, std::milli>(m_stop - m_start).count();
	else if (u == ns)
		return std::chrono::duration<long double, std::nano>(m_stop - m_start).count();
	else
		return 0.0;
}

std::string Stopwatch::pre(const unit &u, const int &precision) //precision of floating point
{
	switch (u)
	{
		case s:
		{
			if (precision > 100)
				return std::to_string(get(s)) + "s";
			else
				return round(get(s), precision) + "s";
		}
		case ms:
		{
			if (precision > 100)
				return std::to_string(get(ms)) + "ms";
			else
				return round(get(ns), precision) + "ms";
		}
		case ns:
		{
			if (precision > 100)
				return std::to_string(get(ns)) + "ns";
			else
				return round(get(ns), precision) + "ns";
		}
		default:
			return "NULL";
	}
}
