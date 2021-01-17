// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef LC_HPP_INCLUDED
#define LC_HPP_INCLUDED

//standard libraries
#include <deque>
#include <vector>
#include <string>

//forward function declarations

class Status
{
  const std::string stat[8] = {"―", "\\", "|", "/", "―", "\\", "|", "/"};
  short pos = 0;

public:
  std::string get();
};

void cpuMeter(const bool &bypass = false);
void statusMeter();

// LCCore == LiveChat Core
namespace LCCore
{
  void DrawHUD();
  void ShowChat();
  void ForceReload();
  void GetChat(const bool &init = false);
  void MoveLogs();
  void CheckMessages(const bool &pre);
  bool CheckInput();
  bool MainLoop();
} // namespace LCCore

#endif