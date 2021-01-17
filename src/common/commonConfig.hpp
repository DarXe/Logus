// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef COMMONCONFIG_HPP_INCLUDED
#define COMMONCONFIG_HPP_INCLUDED

//standard libraries
#include <string>
#include <string_view>

int cfgInput(bool isCls, std::string_view text, std::string_view inputText, std::string_view errorText, std::string_view minMaxText, int min = 0, int max = 0);

std::string cfgInput(bool isCls, std::string_view text, std::string_view inputText, std::string_view errorText);

int cfgSelection(const std::string &Question = "",
                 const std::string &Answer = "",
                 const std::string &Answer2 = "",
                 const std::string &Answer3 = "",
                 const std::string &Answer4 = "");

std::string cfgSelectionStr(const std::string &Question = "",
                            const std::string &Answer = "",
                            const std::string &Answer2 = "",
                            const std::string &Answer3 = "",
                            const std::string &Answer4 = "",
                            const std::string &Answer5 = "",
                            const std::string &Answer6 = "",
                            const std::string &Answer7 = "");

#endif