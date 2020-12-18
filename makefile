CC				 = g++
CFLAGS			 = -g -Os -std=c++17 -I src/common -Wall -Wno-sign-compare -Wno-type-limits -Wno-maybe-uninitialized -Wno-comment
EXEFLAGS		 = $(CFLAGS) -s
PROGRAM_NAME	 = Logus
SRCFILES		:= $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
SRCFILES		+= $(patsubst %.cpp,%.o,$(wildcard src/common/*.cpp))
SRCFILES		+= $(patsubst %.cpp,%.o,$(wildcard src/menu/*.cpp))
SRCFILES		+= $(patsubst %.cpp,%.o,$(wildcard src/addons/*.cpp))
SRCFILES		+= $(patsubst %.cpp,%.o,$(wildcard src/menu/livechat/*.cpp))
CFILES			:= $(subst src/ver.o,,${SRCFILES})
DEPS			:= $(SRCFILES:.o=.d)
PREH			:= $(SRCFILES:.o=.hpp.gch)

default: release

release: $(CFILES) res.res
	$(CC) $(CFLAGS) -c src/ver.cpp -o src/ver.o
	$(CC) $(EXEFLAGS) $(SRCFILES) res.res -o $(PROGRAM_NAME)
	@./Logus.exe "placeholder"

debug: $(SRCFILES) res.res
	$(CC) $(CFLAGS) $^ -o $(PROGRAM_NAME) 

headertest: $(PREH)

res.res: res.rc
	windres $< -O coff -o $@

%.o: %.cpp
	$(CC) -MMD $(CFLAGS) -c $< -o $@

%.hpp.gch: %.hpp
	$(CC) -fsyntax-only $(CFLAGS) -x c++-header $<

clean:
	del /s *.o *.d *.hpp.gch

cleanall:
	del /s *.o *.d *.hpp.gch Logus.exe

rebuild:
	del /s *.o *.d *.hpp.gch
	$(MAKE) --no-print-directory release

-include $(DEPS)