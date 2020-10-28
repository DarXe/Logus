// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef PROC_HPP_INCLUDED
#define PROC_HPP_INCLUDED


//standard libraries
#include <string>


//forward declarations
void color(std::string value);

void serverConnect();

bool runLiveChat();

bool closeLogus(std::string text = "Bye bye");

void stopAutoJoin(bool &isAutoJoin);

void dots(short duration, short amount);

void preConfig();


#endif