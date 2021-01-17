// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef LL_HPP_INCLUDED
#define LL_HPP_INCLUDED

//standard libraries
#include <deque>
#include <string>

enum Editor
{
  DefEditor,
  Logus,
  LiveChat
};

bool checkDate(std::string line, const std::string &date, const bool &checkHour = 0);

void showLogContentInLiveChat(const std::deque<std::string> &foundLines);

bool showLogContentInLogus(const std::string &filename, const uintmax_t &filesize, std::deque<std::string> &foundLines);

bool showLogContentInDefEditor(const std::string &filename, const uintmax_t &filesize, const std::deque<std::string> &foundLines);

bool checkLogNicknames(const std::string &filename);

bool checkLogPM(const std::string &filename, const Editor &editor = DefEditor);

bool checkLogTransfers(const std::string &filename, const Editor &editor = DefEditor);

bool checkLogTransfersAll(const Editor &editor = Logus);

bool checkLogTeam(const std::string &filename);

bool CheckLogContentDateFromTo(const std::string &filename, const std::string &date, const std::string &dateEnd, const bool &checkHour = 0);

void dateSelectionMenu();

void findWordAll_NonCaseSensitive(std::string &word);

void findWordAll_CaseSensitive(std::string &word);

#endif