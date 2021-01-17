// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef LCPROC_HPP_INCLUDED
#define LCPROC_HPP_INCLUDED

//standard libraries
#include <string>

namespace LCEventHandler
{
  void CheckEventHandlers(const std::string &line);

  void PmFrom(const std::string_view line);
  void Team(const std::string_view line);
  void Nicknames(const std::string_view line);
  void Transport(const std::string_view line);
  void Report(const std::string_view line);
  void TransfersFrom(const std::string_view line);
  void BindKey(const std::string_view line);
  void Freeze(const std::string &line);
  void NickChange(const std::string_view line);
  void ContainsPhrase(const std::string_view line);
} // namespace LCEventHandler

void salaryForTransport(const std::string_view line, const bool &type);

#endif