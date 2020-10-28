// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//standard libraries
#include <fstream>
#include <future>


//header includes
#include <common.hpp>
#include "debug.hpp"

static void parseText(std::string &text, const std::vector <std::string> &content)
{
	for(int i = 0; i < content.size(); i++)
	{
		int found = 0;
		if ((found = text.find("%s", found)) != std::string::npos)
		{
			text.erase(found, 2);
			text.insert(found, content[i]);
			found += 2;
		}
	}
}

void LDebug::DebugOutput(std::string text, const std::vector <std::string> &content)
{
	parseText(text, content);
	auto future = std::async(std::launch::async, [&text]
	{
		std::ofstream save("debugInfoOutput.log", std::ios::out | std::ios::binary | std::ios::app);
		save << getCurrentTime() << text << '\n';
		save.close();
	});
}

void LDebug::InfoOutput(const std::string &line)
{
	auto future = std::async(std::launch::async, [&line]
	{
		std::ofstream save("liveChatInfoOutput.log", std::ios::out | std::ios::binary | std::ios::app);
		save << line;
		save.close();
	});
}