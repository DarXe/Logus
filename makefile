CC             = g++
CFLAGS         = -O3 -std=c++17
PROGRAM_NAME   = Logus
SRCFILES       = $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
MENUFILES      = $(patsubst %.cpp,%.o,$(wildcard src/menu/*.cpp))
ADDONFILES     = $(patsubst %.cpp,%.o,$(wildcard src/addons/*.cpp))


default: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(SRCFILES) $(ADDONFILES) $(MENUFILES) res.res
	$(CC) $(CFLAGS) -s -o $(PROGRAM_NAME) res.res $(SRCFILES) $(ADDONFILES) $(MENUFILES)
	Logus "placeholder"
	@echo kompilacja boza poszla pomyslnie

debug: $(SRCFILES) $(ADDONFILES) $(MENUFILES) res.res
	$(CC) -g $(CFLAGS) -o $(PROGRAM_NAME) $(SRCFILES) $(ADDONFILES) $(MENUFILES)
	@echo kompilacja debug poszla pomyslnie

%.o: %.cpp
	$(CC) -g $(CFLAGS) -c -o $@ $<

res.res: res.rc
	windres res.rc -O coff -o res.res

clean:
	del /s *.o