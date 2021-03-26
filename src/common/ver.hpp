// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef VER_HPP_INCLUDED
#define VER_HPP_INCLUDED

//standard libraries
#include <string>
#include <iomanip>

long long getLogusBuildVersion();
std::string getLogusBuildType();

// Variants:
// - 0: YY.MM.DD-S
// - 1: YY.MM.DD
// - 2: YY.MM
std::string getHumanReadableVersion(short variant, std::time_t timestamp = getLogusBuildVersion() / 1000);

#endif