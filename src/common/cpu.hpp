// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef CPU_HPP_INCLUDED
#define CPU_HPP_INCLUDED


//standard libraries
#include <windows.h>
#include <mutex>
#include <timer.hpp>

class CpuUsage
{
public:
	CpuUsage();
	void init();
	void clear();
	double getCpuUsage();
	double getCpuAvg();
	bool ready();

private:
	float avg;
	ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
	unsigned long long avgcount;
	size_t time;
	int numProcessors;
	HANDLE self;
	Timer t;
};

#endif