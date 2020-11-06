// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef CPU_HPP_INCLUDED
#define CPU_HPP_INCLUDED


//standard libraries
#include <windows.h>

class CpuUsage
{
	ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
	long double avg;
	int numProcessors;
	HANDLE self;
public:
	int avgcount = 1;

	CpuUsage();
	void init();
	double getCpuUsage();
	double getCpuAvg();
};

#endif