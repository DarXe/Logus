// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LCEVENTS_HPP_INCLUDED
#define LCEVENTS_HPP_INCLUDED


//standard libraries
#include <string>

namespace LCEvent
{

	bool Team(const std::string &line, const bool &nicksearch);

	bool PwOd(const std::string &line);

	bool PwDo(const std::string &line);

	bool PrzelewyOd(const std::string &line);

	bool PrzelewyDo(const std::string &line);

	bool Komunikat(const std::string &line);

	bool Transport(const std::string &line);

	bool Nicknames(const std::string &line);

	bool BindKey(const std::string &line);

	bool Open(const std::string &line);

	bool PlayerCount(const std::string &line);

	bool Player(const std::string &line);

}

	bool liveChatBeep(std::string &ostatniaLinia);

	void pKarambol(const std::string &line);



#endif
