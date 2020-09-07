CC             = g++
CFLAGS         = -g -O3 -std=c++17
EXEFLAGS       = $(CFLAGS) -s
PROGRAM_NAME   = Logus
SRCFILES      := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
SRCFILES      += $(patsubst %.cpp,%.o,$(wildcard src/menu/*.cpp))
SRCFILES      += $(patsubst %.cpp,%.o,$(wildcard src/addons/*.cpp))
DEPS := $(SRCFILES:.o=.d)

default: release

release: $(SRCFILES) res.res
	$(CC) $(CFLAGS) -c -o src/ver.o src/ver.cpp
	$(CC) $(EXEFLAGS) -o $(PROGRAM_NAME) $^
	@Logus "placeholder"
	@echo kompilacja boza poszla pomyslnie

debug: $(SRCFILES) res.res
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $^
	@echo kompilacja debug poszla pomyslnie

res.res: res.rc
	windres $< -O coff -o $@

%.o: %.cpp
	$(CC) -MMD $(CFLAGS) -c -o $@ $<

clean:
	del /s *.o *.d

cleanall:
	del /s *.o *.d Logus.exe

rebuild:
	del /s *.o *.d
	$(MAKE) --no-print-directory release

-include $(DEPS)