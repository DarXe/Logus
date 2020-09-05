// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef _RANDOM_LOGUS_HPP
#define _RANDOM_LOGUS_HPP

#include "..\libs.hpp"
#include "..\var.hpp"

int lottoLogus();
void lottoLogusReplay(std::vector <std::string> &nicknames, std::vector <short> &playersId, std::vector <std::string> &winners, std::vector <short> &winnersId);
void lottoLogusStats(std::vector <std::string> &nicknames);
void playerList(std::vector <std::string> &nicknames);

#endif