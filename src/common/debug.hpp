// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED


//standard libraries
#include <string>
#include <vector>

namespace LDebug
{
	void DebugOutput(std::string text, const std::vector <std::string> &content);
	void InfoOutput(const std::string_view line);
}

#endif