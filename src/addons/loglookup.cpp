// Copyright © 2020  Niventill

bool checkDate(std::string line, const std::string date, const bool &checkHour = 0)
{
	//used date format (same as in mta logs) [2020-08-28 02:30:15]
	if (!checkHour)
	{
		line = line.substr(1, 10);
		int l_year, l_month, l_day,
		d_year, d_month, d_day;
		sscanf_s(line.c_str(), "%4d-%2d-%2d",
		&l_year, &l_month, &l_day);
		sscanf_s(date.c_str(), "%4d-%2d-%2d",
		&d_year, &d_month, &d_day);

		if (l_year >= d_year)
			if (l_month >= d_month)
				if (l_day >= d_day)
					return 1;
	}
	else
	{
		line = line.substr(1, 16);
		int l_year, l_month, l_day, l_hour, l_minute,
			d_year, d_month, d_day, d_hour, d_minute;
		sscanf_s(line.c_str(), "%4d-%2d-%2d %2d:%2d",
		&l_year, &l_month, &l_day, &l_hour, &l_minute);
		sscanf_s(date.c_str(), "%4d-%2d-%2d %2d:%2d",
		&d_year, &d_month, &d_day, &d_hour, &d_minute);

		if (l_year >= d_year)
			if (l_month >= d_month)
				if (l_day >= d_day)
					if (l_hour >= d_hour)
						if (l_minute >= d_minute)
							return 1;
	}
	return 0;
}

bool showFileContent(const std::string &filename, const uintmax_t &filesize, const std::vector <std::string> &foundLines)
{
	if (foundLines.size() == 0)
	{
		cls();
		std::cout<< ((engLang)?" (INFO) Nothing has been found\n":" (INFO) Nic nie znaleziono\n");
		return 1;
	}
	std::fstream showFile("content.txt", std::ios::out | std::ios::binary);
	std::string line;
	auto showf = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < foundLines.size(); i++)
	{
		line = foundLines.at(i);
		showFile << line << '\n';
	}
	auto showf1 = std::chrono::high_resolution_clock::now();
	auto fshow = std::chrono::duration_cast<std::chrono::nanoseconds>(showf1 - showf).count();
	std::ofstream save;
	save.open("debugInfoOutput.log", std::ios::out | std::ios::binary | std::ios::app);
	save << getCurrentTime() <<"showFileContent: plik: " << filename
		 << " wielkość pliku: " << filesize/1000 << "KB, czas zapisu: " 
		 << fshow << "ns (" << fshow/1000000 << "ms)\n";
	save.close();
	showFile.close();
	cls();
	std::cout << ((engLang)?"Current file: ":"Aktualny plik: ") << filename <<((engLang)?"\nFound content will be shown in default program associated with .txt extension\nPress ESC to return to menu or any other key to continue":
	"\nZnaleziona zawartość pokaże się w edytorze domyślnie ustalonym dla rozszerzenia .txt\nWciśnij klawisz ESC aby powrócić do MENU lub inny żeby kontynuować");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	ShellExecute(0, 0, "content.txt", 0, 0 , SW_SHOW );
	if (getch() == 27)
	{
		remove("content.txt");
		cls();
		return 0;
	}
	remove("content.txt");
	cls();
	return 1;
}

bool checkFileNicknames(const std::string filename)
{
	std::ifstream fileCheck;
	std::string line;
	std::vector <std::string> foundLines;
	auto filesize = std::filesystem::file_size(filename);
	if (filesize>1000000000)
	{
		std::cout<< ((engLang)?" (INFO) File is to big\n":" (INFO) Plik jest za duży\n");
		return 1;
	}

	fileCheck.open(filename, std::ios::in | std::ios::binary);
	while(!fileCheck.eof())
	{
		getline(fileCheck, line);
		if (fNicknames(line))
			foundLines.push_back(line);
	}
	fileCheck.close();

	if (!showFileContent(filename, filesize, foundLines))
		return 0;
	return 1;
}

bool checkFilePM(const std::string filename)
{
	std::ifstream fileCheck;
	std::string line;
	std::vector <std::string> foundLines;
	auto filesize = std::filesystem::file_size(filename);
	if (filesize>1000000000)
	{
		std::cout<< ((engLang)?" (INFO) File is to big\n":" (INFO) Plik jest za duży\n");
		return 1;
	}

	fileCheck.open(filename, std::ios::in | std::ios::binary);
	while(!fileCheck.eof())
	{
		getline(fileCheck, line);
		if (fPwOd(line) || fPwDo(line))
			foundLines.push_back(line);
	}
	fileCheck.close();

	if (!showFileContent(filename, filesize, foundLines))
		return 0;
	return 1;
}

bool checkFileTransfers(const std::string filename)
{
	std::ifstream fileCheck;
	std::string line;
	std::vector <std::string> foundLines;
	auto filesize = std::filesystem::file_size(filename);
	if (filesize>1000000000)
	{
		std::cout<< ((engLang)?" (INFO) File is to big\n":" (INFO) Plik jest za duży\n");
		return 1;
	}
	
	fileCheck.open(filename, std::ios::in | std::ios::binary);
	while(!fileCheck.eof())
	{
		getline(fileCheck, line);
		if (fPrzelewyOd(line) || fPrzelewyDo(line))
			foundLines.push_back(line);
	}
	fileCheck.close();

	if (!showFileContent(filename, filesize, foundLines))
		return 0;
	return 1;
}

bool checkFileTeam(const std::string filename)
{
	std::ifstream fileCheck;
	std::string line;
	std::vector <std::string> foundLines;
	auto filesize = std::filesystem::file_size(filename);
	if (filesize>1000000000)
	{
		std::cout<< ((engLang)?" (INFO) File is to big\n":" (INFO) Plik jest za duży\n");
		return 1;
	}
	
	fileCheck.open(filename, std::ios::in | std::ios::binary);
	while(!fileCheck.eof())
	{
		getline(fileCheck, line);
		if (fTeam(line, 0))
			foundLines.push_back(line);
	}
	fileCheck.close();

	if (!showFileContent(filename, filesize, foundLines))
		return 0;
	return 1;
}

bool checkFileDateFromTo(const std::string &filename, const std::string &date, const std::string &dateEnd, const bool &checkHour = 0)
{
	std::ifstream fileCheck;
	std::string line;
	std::vector <std::string> foundLines;
	auto filesize = std::filesystem::file_size(filename);
	if (filesize>1000000000)
	{
		std::cout<< ((engLang)?" (INFO) File is to big\n":" (INFO) Plik jest za duży\n");
		return 1;
	}
	
	fileCheck.open(filename, std::ios::in | std::ios::binary);
	while(!fileCheck.eof())
	{
		getline(fileCheck, line);
		if (checkDate(line, date, checkHour))
		{
			foundLines.push_back(line);
			break;
		}
	}
	while(!fileCheck.eof())
	{
		getline(fileCheck, line);
		foundLines.push_back(line);
		if (checkDate(line, dateEnd, checkHour))
			break;
	}
	fileCheck.close();

	showFileContent(filename, filesize, foundLines);
	return 1;
}

void dateSelectionMenu()
{
	std::string date, dateEnd, filename;
	cls();
	if(engLang)
	{

	}
	else
	{
		filename = ((engLang)?cfgSelectionStr("Choose file to lookup.", "console.log", "console.log.1", "console.log.2", "console.log.3", "console.log.4", "console.log.5", "logus.log"):
										cfgSelectionStr("Wybierz nazwę pliku do przeszukania.", "console.log", "console.log.1", "console.log.2", "console.log.3", "console.log.4", "console.log.5", "logus.log"));
		if (filename == "WYJSCIE")
			return;
		cls();
		if(cfgSelection(0, "Czy chcesz uwzględnić w wyszukiwaniu także godzinę?", "Tak", "Nie"))
		{
			date = cfgInputString(0, 1, "Podaj datę początkową (przykładowo 2020-08-28 21:37)", "Podaj datę (obowiązkowo format RRRR-MM-DD HH:MM):", "Nie wiem jak, ale coś podałeś źle");
			dateEnd = cfgInputString(0, 1, "Podaj datę końcową (przykładowo 2020-08-29 21:37)", "Podaj datę (obowiązkowo format RRRR-MM-DD HH:MM):", "Nie wiem jak, ale coś podałeś źle");
			cls();
			checkFileDateFromTo(filename, date, dateEnd, 1);
			return;
		}
		else
		{
			date = cfgInputString(0, 1, "Podaj datę początkową (przykładowo 2020-08-28)", "Podaj datę (obowiązkowo format RRRR-MM-DD):", "Nie wiem jak, ale coś podałeś źle");
			dateEnd = cfgInputString(0, 1, "Podaj datę końcową (przykładowo 2020-08-29)", "Podaj datę (obowiązkowo format RRRR-MM-DD):", "Nie wiem jak, ale coś podałeś źle");
			cls();
			checkFileDateFromTo(filename, date, dateEnd, 0);
			return;
		}
	}
}