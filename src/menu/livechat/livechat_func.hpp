// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LCFUNC_HPP_INCLUDED
#define LCFUNC_HPP_INCLUDED


//standard libraries
#include <string>


//forward declarations
bool fTeam(const std::string &line, bool e);

void pKarambol(const std::string &line);

bool fPwOd(const std::string &line);

bool fPwDo(const std::string &line);

void pNickChange(const std::string &line);

bool fPrzelewyOd(const std::string &line);

bool fPrzelewyDo(const std::string &line);

bool fKomunikat(const std::string &line);

bool fTransport(const std::string &line);

bool fNicknames(const std::string &line);

bool fBindKey(const std::string &line);

bool fOpen(const std::string &line);

bool player(const std::string &line);

bool fPlayerCount(const std::string &line);

char fConsoleInput(const std::string &line);

bool liveChatBeep(std::string &ostatniaLinia);


#endif