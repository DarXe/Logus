// Copyright © 2018-2020  DarXe

#ifndef _RANDOM_LOGUS_HPP
#define _RANDOM_LOGUS_HPP

int lottoLogus();
void lottoLogusReplay(std::vector <std::string> &nicknames, std::vector <short> &playersId, std::vector <std::string> &winners, std::vector <short> &winnersId);
void lottoLogusStats(std::vector <std::string> &nicknames);
void playerList(std::vector <std::string> &nicknames);

#endif