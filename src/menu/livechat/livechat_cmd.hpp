// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LCCMD_HPP_INCLUDED
#define LCCMD_HPP_INCLUDED


//standard libraries
#include <string>
#include <string_view>

namespace LCCommand
{
	void CheckCommandInput(const std::string &line);
	void PreCheckCommandInput(const std::string &line);

	void Reconnect(const std::string_view line);
	void Quit(const std::string_view line);
	void StartTimer(const std::string_view linee);
	void SetNick(const std::string &line);
	void SetTrack(const std::string_view line);
	void SetTimer(const std::string_view line);
	void AddNickname(const std::string_view line);
	void DelNickname(const std::string_view line);
	void SetMoney(const std::string &line);
	void SetCourses(const std::string &line);
	void Reset(const std::string_view line);
	void HardReset(const std::string_view line);
	void FindTransfers(const std::string_view line);
	void FindWord(const std::string &line);
	void FindConfig(const std::string_view line);
	void FindConsoleLog(const std::string_view line);
	void FindLogusLog(const std::string_view line);
	void Timestamp(const std::string_view line);
	void TimestampBeep(const std::string_view line);
	void ClearEngine(const std::string_view line);
	void ClearEngineBeep(const std::string_view line);
} // namespace LCCommand

#endif
