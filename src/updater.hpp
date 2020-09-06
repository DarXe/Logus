// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef UPDATER_HPP_INCLUDED
#define UPDATER_HPP_INCLUDED

#include "..\src\libs.hpp"
#include "..\src\var.hpp"
#include "..\src\config.hpp"
#include "..\src\ver.hpp"

void checkLogusUpdate();

void updateDependencies();

void checkUpdates();

#endif