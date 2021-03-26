// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <iostream>

//header includes
#include "ver.hpp"

long long getLogusBuildVersion()
{
  return __LOGUS_BUILD_TIMESTAMP__;
}

std::string getLogusBuildType()
{
  return __LOGUS_BUILD_TYPE__;
}

std::string getHumanReadableVersion(short variant, std::time_t timestamp)
{
  struct tm * dt;
  char buffer [30];
  dt = localtime(&timestamp);
  switch (variant)
  {
    case 0: strftime(buffer, sizeof(buffer), "%y.%m.%d-%S", dt);
    break;
    case 1: strftime(buffer, sizeof(buffer), "%y.%m.%d", dt);
    break;
    case 2: strftime(buffer, sizeof(buffer), "%y.%m", dt);
    break;
  }
  return std::string(buffer);
}
