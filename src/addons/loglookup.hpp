// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef LL_HPP_INCLUDED
#define LL_HPP_INCLUDED

#include "..\libs.hpp"
#include "..\proc.hpp"
#include "..\menu\livechat_func.hpp"

bool checkDate(std::string line, const std::string &date, const bool &checkHour = 0);

bool showFileContent(const std::string &filename, const uintmax_t &filesize, const std::vector <std::string> &foundLines);

bool checkFileNicknames(const std::string &filename);

bool checkFilePM(const std::string &filename);

bool checkFileTransfers(const std::string &filename);

bool checkFileTeam(const std::string &filename);

bool checkFileDateFromTo(const std::string &filename, const std::string &date, const std::string &dateEnd, const bool &checkHour = 0);

void dateSelectionMenu();

#endif