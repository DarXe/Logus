// Copyright © 2018-2020  DarXe, Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.



void startTimer(short getSeconds)
{
	Beep(dzwiekGlowny, 100);
	delay = clock();
	if(getSeconds)
	{
		timer = getSeconds*1000;
	}
	else
	{
		timer = czas*1000;
		if(random) timer += 300000; else timer += 360000;
		isCzas = 1;
	}
	isTimer = 1;
	pos.X=0; pos.Y=2; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 170); std::cout<<" "; SetConsoleTextAttribute(h, 12);
	std::cout<<" Timer 0:00  [s]Stop Timer   ";
}

void stopTimer()
{
	Beep(dzwiekGlowny, 500);
	isTimer = 0;
	isCzas = 0;
	timer = 0;
	pos.X=0; pos.Y=2; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
}

void salaryForTransport(std::string &line)
{
	//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	short delim = 0, delim1 = 0; std::string tempSalary;
	if (line.find("rt ") != std::string::npos) //pol if
		delim = line.find("rt ");
	else if (line.find("d $") != std::string::npos) //eng if
		delim = line.find("d $");

	if (line.find("$ z") != std::string::npos) //pol if
		delim1 = line.find("$ z");
	else if (line.find(". I") != std::string::npos) //eng if
		delim1 = line.find(". I");

	tempSalary = line.substr(delim+3, delim1-delim-3);
	money += stoi(tempSalary);
	courses++;
	saveConfig(0);
}

void stopAutoJoin(bool &isAutoJoin)
{
	isAutoJoin = false;
	pos.X=3; pos.Y=4; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 12); std::cout<<"       CONNECTED!       ";
	Beep(dzwiekGlowny, 500);
}