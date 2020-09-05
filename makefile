CC           = g++
CFLAGS       = -O3 -std=c++17 -s
PROGRAM_NAME = Logus
SRCFILES       = $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
MENUFILES       = $(patsubst %.cpp,%.o,$(wildcard src/menu/*.cpp))
ADDONFILES       = $(patsubst %.cpp,%.o,$(wildcard src/addons/*.cpp))


default: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(SRCFILES) $(ADDONFILES) $(MENUFILES) res.res
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) res.res $(SRCFILES) $(ADDONFILES) $(MENUFILES)
	@echo kompilacja boza poszla pomyslnie

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo rekompilacja pliku $@

res.res: res.rc
	windres res.rc -O coff -o res.res

clean:
	del /s *.o