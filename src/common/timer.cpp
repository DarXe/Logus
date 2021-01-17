// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//standard libraries
#include <iostream>
#include <windows.h>

//header includes
#include <var.hpp>
#include "timer.hpp"

Timer::Timer()
    : timer(0), running(0), loaded(0), m_delay(0) {}

void Timer::start(const clock_t &_timer, const bool &beep) //in ms
{
  timer = _timer;
  m_delay = clock();
  running = true;
  if (beep)
    Beep(dzwiekGlowny, 100);
}

void Timer::stop(const bool &beep)
{
  if (running)
  {
    timer = 0;
    if (beep)
      Beep(dzwiekGlowny, 500);
    running = false;
    loaded = false;
  }
}

void Timer::startCounter(const short &getSeconds)
{
  if (getSeconds)
  {
    start(getSeconds * 1000);
  }
  else
  {
    start(czas * 1000);
    if (random)
      timer += 300000;
    else
      timer += 360000;
    loaded = true;
  }
  COORD pos;
  pos.X = 0;
  pos.Y = 2;
  SetConsoleCursorPosition(h, pos);
  SetConsoleTextAttribute(h, 170);
  std::cout << " ";
  SetConsoleTextAttribute(h, 12);
}

void Timer::stopCounter()
{
  COORD pos;
  stop();
  pos.X = 0;
  pos.Y = 2;
  SetConsoleCursorPosition(h, pos);
  SetConsoleTextAttribute(h, 204);
  std::cout << " ";
  SetConsoleTextAttribute(h, 12);
}

void Timer::update()
{
  if (running)
  {
    timer -= (clock() - m_delay);
    m_delay = clock();
  }
}

void Timer::beep()
{
  if (running)
  {
    if (timer > 0)
    {
      update();
      if (loaded)
        if ((timer < 300000 && random) || (!random && timer < 360000))
        {
          Beep(dzwiekGlowny, 150);
          Beep(0, interval);
          Beep(dzwiekGlowny + 50, 150);
          Beep(0, interval);
          Beep(dzwiekGlowny + 100, 150);
          Beep(0, interval);
          loaded = 0;
        }
    }
    else
    {
      Beep(dzwiekGlowny - 100, 150);
      Beep(0, interval);
      Beep(dzwiekGlowny - 50, 150);
      Beep(0, interval);
      Beep(dzwiekGlowny, 150);
      Beep(0, interval);
      mainTimer.stop(false);
      COORD pos;
      pos.X = 0;
      pos.Y = 2;
      SetConsoleCursorPosition(h, pos);
      SetConsoleTextAttribute(h, 204);
      std::cout << " ";
      SetConsoleTextAttribute(h, 12);
      pos.X = 1;
      pos.Y = 2;
      SetConsoleCursorPosition(h, pos);
      std::cout << " [t]Timer                  ";
    }
  }
}

int Timer::getMs()
{
  return timer;
}

int Timer::getSec()
{
  return timer / 1000;
}

std::string Timer::getTime()
{
  std::string m, s;
  //minutes
  if ((getSec() / 60) % 60 < 10)
    m = "0" + std::to_string(getSec() / 60);
  else
    m = std::to_string(getSec() / 60);

  //seconds
  if (getSec() % 60 < 10)
    s = "0" + std::to_string(getSec() % 60);
  else
    s = std::to_string(getSec() % 60);

  return m + ":" + s;
}