// Copyright © 2020  Niventill

bool checkDate(const std::string line, std::string date, const bool checkHour = 0)
{
	//used date format (same as in mta logs) [2020-08-28 02:30:15]
	if (!checkHour)
		date = date.substr(1, 10);
	else
		date = date.substr(1, 16);
	if (line.find(date) != std::string::npos)
		return 1;
	return 0;
}

bool showFileContent(const std::string &filename, const uintmax_t &filesize, const std::vector <std::string> &foundLines)
{
	if (foundLines.size() == 0)
		return 1;
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
	save.open("liveChatInfoOutput.log", std::ios::out | std::ios::binary | std::ios::app);
	save << getCurrentTime() <<"showFileContent: plik: " << filename
		 << " wielkość pliku: " << filesize/1000 << "KB, czas zapisu: " 
		 << fshow << "ns (" << fshow/1000000 << "ms)\n";
	save.close();
	cls();
	std::cout << ((engLang)?"Current file: ":"Aktualny plik: ") << filename <<((engLang)?"\nFound content will be shown in default program associated with .txt extension\nPress ESC to return to menu or any other key to continue":
	"\nZnaleziona zawartość pokaże się w edytorze domyślnie ustalonym dla rozszerzenia .txt\nWciśnij klawisz ESC aby powrócić do MENU lub inny żeby kontynuować");
	ShellExecute(0, 0, "content.txt", 0, 0 , SW_SHOW );
	if (getch() == 27)
	{
		showFile.close();
		remove("content.txt");
		cls();
		return 0;
	}
	showFile.close();
	remove("content.txt");
	cls();
	return 1;
}

bool checkFileNicknames(const std::string filename, const bool checkAllFiles = 0, const bool isRecursive = 0)
{
	std::ifstream fileCheck;
	std::string line;
	std::vector <std::string> foundLines;
	auto filesize = std::filesystem::file_size(filename);
	fileCheck.open(filename, std::ios::in | std::ios::binary);
	while(!fileCheck.eof() && filesize < 100000000)
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

bool checkFilePM(const std::string filename, const bool checkAllFiles = 0, const bool isRecursive = 0)
{
	std::ifstream fileCheck;
	std::string line;
	std::vector <std::string> foundLines;
	auto filesize = std::filesystem::file_size(filename);

	fileCheck.open(filename, std::ios::in | std::ios::binary);
	while(!fileCheck.eof() && filesize < 100000000)
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
	
	fileCheck.open(filename, std::ios::in | std::ios::binary);
	while(!fileCheck.eof() && filesize < 100000000)
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

bool checkFileTeam(const std::string filename, const bool checkAllFiles = 0, const bool isRecursive = 0)
{
	std::ifstream fileCheck;
	std::string line;
	std::vector <std::string> foundLines;
	auto filesize = std::filesystem::file_size(filename);
	
	fileCheck.open(filename, std::ios::in | std::ios::binary);
	while(!fileCheck.eof() && filesize < 100000000)
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

