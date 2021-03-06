// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef LCFORMAT_HPP_INCLUDED
#define LCFORMAT_HPP_INCLUDED

//standard libraries
#include <string_view>
#include <deque>

namespace LCFormat
{
  bool isNewLine(std::string_view line);
  void Standard(std::string_view line);
  void NonStandard(std::string_view line);
  void Transfers(std::string_view line);
  void Info(std::string_view line);
  void Input(std::string_view line);
  void ContainsPhrase(std::string_view line);
  void Default(std::string_view line);
  void Nothing(std::string_view line);
  void SetColor(const short &color);
  void ParseLines(const std::deque<std::string> &lastLines, std::deque<int> &lastLinesSize, const bool &timestamp = false);
} // namespace LCFormat

#endif
