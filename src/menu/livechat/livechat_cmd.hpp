// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LCCMD_HPP_INCLUDED
#define LCCMD_HPP_INCLUDED


//standard libraries
#include <string>

namespace LCCommand
{
	void CheckCommandInput(const std::string &line);

	inline void Reconnect(const std::string &line);
	inline void Quit(const std::string &line);
	inline void StartTimer(const std::string &line);
	inline void SetNick(const std::string &line);
	inline void SetTrack(const std::string &line);
	inline void SetTimer(const std::string &line);
	inline void AddNickname(const std::string &line);
	inline void DelNickname(const std::string &line);
	inline void SetMoney(const std::string &line);
	inline void SetCourses(const std::string &line);
	inline void Reset(const std::string &line);
	inline void HardReset(const std::string &line);
	inline void FindTransfers(const std::string &line);
	inline void FindWord(const std::string &line);
	inline void FindConfig(const std::string &line);
	inline void FindConsoleLog(const std::string &line);
	inline void FindLogusLog(const std::string &line);
} // namespace LCCommand

#endif
