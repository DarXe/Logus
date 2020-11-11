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
	void PreCheckCommandInput(const std::string &line, bool &isAutoJoin);

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
	void SetLoadingTime(const std::string_view line);
	void Reset(const std::string_view line);
	void HardReset(const std::string_view line);
	void FindTransfers(const std::string_view line);
	void FindWord(const std::string &line);
	void OpenConfig(const std::string_view line);
	void OpenConsoleLog(const std::string_view line);
	void OpenLogusLog(const std::string_view line);
	void Timestamp(const std::string_view line);
	void TimestampBeep(const std::string_view line);
	void RenderEngine(const std::string_view line);
	void RenderEngineBeep(const std::string_view line);
	void ClearChat(const std::string_view line);
	void ClearChatBeep(const std::string_view line);
	void SetMax(const std::string &line);
	void SetMin(const std::string &line);
	void SetRefresh(const std::string &line);
	void SetDynamicRefresh(const std::string_view line);
	void SetDynamicRefreshBeep(const std::string_view line);
	void AutoReconnect(const std::string_view line, bool &isAutoJoin);
	void AutoReconnectBeep(const std::string_view line);
} // namespace LCCommand

namespace LCCmdEvent
{
	bool Reconnect(const std::string_view line);
	bool Quit(const std::string_view line);
	bool StartTimer(const std::string_view linee);
	bool SetNick(const std::string_view line);
	bool SetTrack(const std::string_view line);
	bool SetTimer(const std::string_view line);
	bool AddNickname(const std::string_view line);
	bool DelNickname(const std::string_view line);
	bool SetMoney(const std::string_view line);
	bool SetCourses(const std::string_view line);
	bool SetLoadingTime(const std::string_view line);
	bool Reset(const std::string_view line);
	bool HardReset(const std::string_view line);
	bool FindTransfers(const std::string_view line);
	bool FindWord(const std::string_view line);
	bool OpenConfig(const std::string_view line);
	bool OpenConsoleLog(const std::string_view line);
	bool OpenLogusLog(const std::string_view line);
	bool Timestamp(const std::string_view line);
	bool RenderEngine(const std::string_view line);
	bool ClearChat(const std::string_view line);
	bool SetMax(const std::string_view line);
	bool SetMin(const std::string_view line);
	bool SetRefresh(const std::string_view line);
	bool SetDynamicRefresh(const std::string_view line);
	bool AutoReconnect(const std::string_view line);

	bool CheckCommandEvents(const std::string_view line);
} // namespace LCCommand

#endif
