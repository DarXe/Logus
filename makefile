CC             = g++
CFLAGS         = -O3 -std=c++17
PROGRAM_NAME   = Logus
SRCFILES      := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
SRCFILES      += $(patsubst %.cpp,%.o,$(wildcard src/menu/*.cpp))
SRCFILES      += $(patsubst %.cpp,%.o,$(wildcard src/addons/*.cpp))


default: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(SRCFILES) res.res
	$(CC) $(CFLAGS) -s -o $(PROGRAM_NAME) $^
	Logus "placeholder"
	@echo kompilacja boza poszla pomyslnie

debug: $(SRCFILES) res.res
	$(CC) -g $(CFLAGS) -o $(PROGRAM_NAME) $^
	@echo kompilacja debug poszla pomyslnie

res.res: res.rc
	windres res.rc -O coff -o res.res

%.o: %.cpp
	$(CC) -g $(CFLAGS) -c -o $@ $<

clean:
	del /s *.o
