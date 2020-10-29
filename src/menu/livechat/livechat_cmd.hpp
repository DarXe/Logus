// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LCCMD_HPP_INCLUDED
#define LCCMD_HPP_INCLUDED


//standard libraries
#include <string>

namespace LCCommand
{
	void CheckCommandInput(const std::string &line);

	bool Reconnect(const std::string &line);
	bool Quit(const std::string &line);
	bool StartTimer(const std::string &line);
	bool SetNick(const std::string &line);
	short SetTrack(const std::string &line);
	bool SetTimer(const std::string &line);
	bool AddNickname(const std::string &line);
	bool DelNickname(const std::string &line);
	bool SetMoney(const std::string &line);
	bool SetCourses(const std::string &line);
	bool Reset(const std::string &line);
	bool HardReset(const std::string &line);
	bool FindTransfers(const std::string &line);
	bool FindWord(const std::string &line);
	bool FindConfig(const std::string &line);
	bool FindConsoleLog(const std::string &line);
	bool FindLogusLog(const std::string &line);
} // namespace LCCommand

#endif
