// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LCCMD_HPP_INCLUDED
#define LCCMD_HPP_INCLUDED


//standard libraries
#include <string>

class LiveChatCMD
{
public:
	void checkCommandInput(const std::string &line);

	bool reconnect(const std::string &line);
	bool quit(const std::string &line);
	bool startTimer(const std::string &line);
	bool setNick(const std::string &line);
	short setTrack(const std::string &line);
	bool setTimer(const std::string &line);
	bool addNickname(const std::string &line);
	bool delNickname(const std::string &line);
	bool setMoney(const std::string &line);
	bool setCourses(const std::string &line);
	bool reset(const std::string &line);
	bool hardReset(const std::string &line);
};

extern LiveChatCMD cmd;

#endif
