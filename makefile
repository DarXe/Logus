default:

logus: src\main.cpp
	g++ -o Logus.exe src\main.cpp -std=c++17 -O3 -s
	@echo release build done!
logusdev: src\main.cpp
	g++ -o Logus.exe src\main.cpp -std=c++17 -O3 -s -D LOGUSDEV
	@echo dev build done!
logussc: src\main.cpp
	g++ -o Logus.exe src\main.cpp -std=c++17 -O3 -s -D SHOWCURSOR
	@echo release with cursor build done!
updater: src\updater.cpp
	g++ -o updater.exe src\updater.cpp -Ofast -s
	@echo done!
spamer: m.cpp
	g++ -o a.exe m.cpp -Ofast -std=c++17 -s
	@echo done!