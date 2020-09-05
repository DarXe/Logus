// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef LCPROC_HPP_INCLUDED
#define LCPROC_HPP_INCLUDED

#include "..\libs.hpp"
#include "..\config.hpp"

void startTimer(short getSeconds = 0);

void stopTimer();

void salaryForTransport(std::string &line);

void stopAutoJoin(bool &isAutoJoin);


#endif