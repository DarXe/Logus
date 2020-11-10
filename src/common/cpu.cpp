// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <windows.h>


//header includes
#include <timer.hpp>
#include <var.hpp>
#include "cpu.hpp"

void CpuUsage::init()
{
    SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    numProcessors = sysInfo.dwNumberOfProcessors;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&lastCPU, &ftime, sizeof(FILETIME));

    self = GetCurrentProcess();
    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
    memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}

CpuUsage::CpuUsage()
    : avg(0), avgcount(1)
{
	init();
}

void CpuUsage::clear()
{
    avg = 0; avgcount = 1;
}

double CpuUsage::getCpuAvg()
{
    return avg/avgcount;
}

double CpuUsage::getCpuUsage()
{
    FILETIME ftime, fsys, fuser;
    ULARGE_INTEGER now, sys, user;
    double percent;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&now, &ftime, sizeof(FILETIME));

    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&sys, &fsys, sizeof(FILETIME));
    memcpy(&user, &fuser, sizeof(FILETIME));
    percent = (sys.QuadPart - lastSysCPU.QuadPart) +
        (user.QuadPart - lastUserCPU.QuadPart);
    percent /= (now.QuadPart - lastCPU.QuadPart);
    percent /= numProcessors;
    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    avg += (percent * 100);
    avgcount++;

    return percent * 100;
}

bool CpuUsage::ready()
{
    t.update();
    if (t.timer <= 0)
    {
        t.start((refresh), false);
        return 1;
    }
    else
        return 0;
}
