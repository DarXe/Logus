// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LCCMD_HPP_INCLUDED
#define LCCMD_HPP_INCLUDED


//standard libraries
#include <string>

namespace LCCommand
{
	void CheckCommandInput(const std::string &line);

	void Reconnect(const std::string &line);
	void Quit(const std::string &line);
	void StartTimer(const std::string &line);
	void SetNick(const std::string &line);
	void SetTrack(const std::string &line);
	void SetTimer(const std::string &line);
	void AddNickname(const std::string &line);
	void DelNickname(const std::string &line);
	void SetMoney(const std::string &line);
	void SetCourses(const std::string &line);
	void Reset(const std::string &line);
	void HardReset(const std::string &line);
	void FindTransfers(const std::string &line);
	void FindWord(const std::string &line);
	void FindConfig(const std::string &line);
	void FindConsoleLog(const std::string &line);
	void FindLogusLog(const std::string &line);
	void Timestamp(const std::string &line);
} // namespace LCCommand

#endif
