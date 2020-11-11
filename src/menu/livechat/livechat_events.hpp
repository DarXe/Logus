// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LCEVENTS_HPP_INCLUDED
#define LCEVENTS_HPP_INCLUDED


//standard libraries
#include <string>
#include <string_view>

namespace LCEvent
{
	bool Team(const std::string_view line, const bool &includePlayer = false, const bool &onlyPlayer = false);
	bool PmFrom(const std::string_view line);
	bool PmTo(const std::string_view line);
	bool TransfersFrom(const std::string_view line);
	bool TransfersTo(const std::string_view line);
	bool Report(const std::string_view line);
	bool TransportCompany(const std::string_view line);
	bool TransportTruckerzy(const std::string_view line);
	bool Nicknames(const std::string_view line);
	bool BindKey(const std::string_view line);
	bool Open(const std::string_view line);
	//bool Player(const std::string_view line);
	//bool PlayerCount(const std::string_view line);
	bool Freeze(const std::string_view line);
	bool NickChange(const std::string_view line);
	bool ContainsPhrase(const std::string_view line, const bool &format = false);
	bool NormalMessage(const std::string_view line);
	bool Admin(const std::string_view line, const bool &includePlayer);
	bool Input(const std::string_view line);
	bool CB(const std::string_view line);
} // namespace LCEvent

bool notifCheck(std::string_view line);

#endif
