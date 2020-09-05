// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


void updateDependecies()
{
    if (!std::filesystem::exists("bin\\curl.exe"))
    {
        std::filesystem::create_directory("bin");
        std::filesystem::copy("c:\\windows\\system32\\curl.exe", "bin\\curl.exe");
        if (!std::filesystem::exists("bin\\curl.exe"))
            engLang? std::cout<<"Couldn't find curl, auto-update will be limited.\n":
            std::cout<<"Nie udało się znaleźć curl. Możliwości auto-update będą ograniczone.\n";
    }

        std::filesystem::create_directory("bin");
        system("bin\\curl https://raw.githubusercontent.com/DarXe/Logus/master/pasteCmd.exe -z bin\\pasteCmd.exe -o bin\\pasteCmd.exe --location --verbose");
}

void checkUpdate()
{
    if (updateChannel == "release")
    {

    }
}

void runUpdater()
{
    updateDependecies();
}