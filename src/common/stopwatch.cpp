// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>


//header includes
#include "stopwatch.hpp"
#include "common.hpp"

Stopwatch::Stopwatch()
{
	m_start = std::chrono::high_resolution_clock::now();
}

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

long double Stopwatch::get(const std::string &type)
{
	if (type == "s")
		return std::chrono::duration<long double>(m_stop - m_start).count();
	else if (type == "ms")
		return std::chrono::duration<long double, std::milli>(m_stop - m_start).count();
	else if (type == "ns")
		return std::chrono::duration<long double, std::nano>(m_stop - m_start).count();
	else
		return 0.0;
}

std::string Stopwatch::pre(const std::string &type, const int &precision) //precision of floating point
{
	if (type == "s")
		if (precision > 100)
			return std::to_string(get("s")) + "s";
		else
			return round(get("s"), precision) + "s";
	else if (type == "ms")
		if (precision > 100)
			return std::to_string(get("ms")) + "ms";
		else
			return round(get("ms"), precision) + "ms";
	else if (type == "ns")
		if (precision > 100)
			return std::to_string(get("ns")) + "ns";
		else
			return round(get("ns"), precision) + "ns";
	else
		return "NULL";
}
