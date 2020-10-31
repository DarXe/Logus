// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LCPROC_HPP_INCLUDED
#define LCPROC_HPP_INCLUDED


//standard libraries
#include <string>

namespace LCEventHandler
{
	void CheckActions(const std::string &line);

	void PmFrom(const std::string &line);
	void Team(const std::string &line);
	void Nicknames(const std::string &line);
	void Transport(const std::string &line);
	void Report(const std::string &line);
	void TransfersFrom(const std::string &line);
	void BindKey(const std::string &line);
	void Freeze(const std::string &line);
	void NickChange(const std::string &line);
	void SalaryForTransport(const std::string &line);
	void ContainsPhrase(const std::string &line);
} // namespace LCEventHandler

#endif