// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//header includes
#include "ver.hpp"


//letting compiler know that this variable exists without actually including var.hpp
extern std::string relVer;
extern std::string titleVer;


std::string genVer()
{
	// __DATE__
	// Aug  7 2020
	// 01234567890

	std::string month, day, rday, year, tempTime, seconds, t1, t2;
	int tempSeconds;
	std::string cDate = __DATE__;
	//std::string cTime = "00:00:00";
	//std::string cTime = "23:59:59";
	std::string cTime = __TIME__;

	//convert __DATE__ and __TIME_ formats to Logus's versioning system

	//year
	year = (t1 = cDate[9]) + (t2 = cDate[10]);

	//month
	if (cDate.find("Jan") != std::string::npos)
		month = "01";
	if (cDate.find("Feb") != std::string::npos)
		month = "02";
	if (cDate.find("Mar") != std::string::npos)
		month = "03";
	if (cDate.find("Apr") != std::string::npos)
		month = "04";
	if (cDate.find("May") != std::string::npos)
		month = "05";
	if (cDate.find("Jun") != std::string::npos)
		month = "06";
	if (cDate.find("Jul") != std::string::npos)
		month = "07";
	if (cDate.find("Aug") != std::string::npos)
		month = "08";
	if (cDate.find("Sep") != std::string::npos)
		month = "09";
	if (cDate.find("Oct") != std::string::npos)
		month = "10";
	if (cDate.find("Nov") != std::string::npos)
		month = "11";
	if (cDate.find("Dec") != std::string::npos)
		month = "12";

	// day
	if (cDate[4] == ' ')
	{
		day = "0" + (t1 = cDate[5]);
		rday = (t1 = cDate[5]);
	}
	else
		day = (t1 = cDate[4]) + (t2 = cDate[5]);

	// __TIME__
	// 22:22:47 // 1320 + 1320 + 2820 = 5460
	// 01234567

	tempTime = (t1 = cTime[0]) + (t2 = cTime[1]); //hours
	tempSeconds = stoi(tempTime) * 3600;		  //convert to int
	tempTime = (t1 = cTime[3]) + (t2 = cTime[4]); //minutes
	tempSeconds += stoi(tempTime) * 60;			  //convert to int
	tempTime = (t1 = cTime[6]) + (t2 = cTime[7]); //seconds
	tempSeconds += stoi(tempTime);				  //convert to int
	tempSeconds /= 60;							  //edit here if needed
	seconds = std::to_string(tempSeconds);		  //convert int to string

	titleVer = year + "." + month + "." + rday;
	relVer = year + "." + month;
	return year + "." + month + "." + day + "-" + seconds;
}