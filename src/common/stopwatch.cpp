// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//header includes
#include "stopwatch.hpp"
#include "common.hpp"

Stopwatch::Stopwatch()
    : m_start(std::chrono::high_resolution_clock::now()), m_time(0) {}

Stopwatch::~Stopwatch()
{
  m_stop = std::chrono::high_resolution_clock::now();
  m_time = std::chrono::duration<long double, std::nano>(m_stop - m_start).count();
}

void Stopwatch::stop()
{
  m_stop = std::chrono::high_resolution_clock::now();
  m_time = std::chrono::duration<long double, std::nano>(m_stop - m_start).count();
}

long double Stopwatch::get(const unit &u)
{
  switch (u)
  {
  case s:
    return std::chrono::duration<long double>(m_stop - m_start).count();
  case ms:
    return std::chrono::duration<long double, std::milli>(m_stop - m_start).count();
  case ns:
    return std::chrono::duration<long double, std::nano>(m_stop - m_start).count();
  default:
    return 0.0;
  }
}

std::string Stopwatch::pre(const unit &u, const int &precision) //precision of floating point
{
  switch (u)
  {
  case s:
    return round(get(s), precision) + "s";
  case ms:
    return round(get(ms), precision) + "ms";
  case ns:
    return round(get(ns), precision) + "ns";
  default:
    return "NULL";
  }
}
