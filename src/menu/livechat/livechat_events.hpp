// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LCEVENTS_HPP_INCLUDED
#define LCEVENTS_HPP_INCLUDED


//standard libraries
#include <string>

namespace LCEvent
{
	bool Team(const std::string &line, const bool &includePlayer);
	bool PmFrom(const std::string &line);
	bool PmTo(const std::string &line);
	bool TransfersFrom(const std::string &line);
	bool TransfersTo(const std::string &line);
	bool Report(const std::string &line);
	bool Transport(const std::string &line);
	bool Nicknames(const std::string &line);
	bool BindKey(const std::string &line);
	bool Open(const std::string &line);
	//bool Player(const std::string &line);
	//bool PlayerCount(const std::string &line);
	bool Freeze(const std::string &line);
	bool NickChange(const std::string &line);
	bool ContainsPhrase(const std::string &line);
} // namespace LCEvent

bool liveChatBeep(std::string &ostatniaLinia);

#endif
