CC						 = g++
TIMESTAMP				:= $(shell get_timestamp)
COMPILE_FLAGS			 = -g -Os -std=c++17 -I src/common -Wall -Wno-sign-compare -Wno-type-limits -Wno-maybe-uninitialized -Wno-comment -D __LOGUS_BUILD_TIMESTAMP__=$(TIMESTAMP)
PROGRAM_NAME			 = Logus
SOURCE_FILES			:= $(patsubst %.cpp,%.o,$(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp))
RELEASE_BUILD_FILES		 = $(addprefix build/release/,$(SOURCE_FILES))
EXPERIMENTAL_BUILD_FILES = $(addprefix build/experimental/,$(SOURCE_FILES))
DEBUG_BUILD_FILES		 = $(addprefix build/debug/,$(SOURCE_FILES))
DEPENDENCIES			:= $(subst src/,build/release/,$(SOURCE_FILES:.o=.d))
DEPENDENCIES			+= $(subst src/,build/experimental/,$(SOURCE_FILES:.o=.d))
SHELL=cmd

default: release

all: release experimental debug

release: $(RELEASE_BUILD_FILES) res.res
	$(CC) $(COMPILE_FLAGS) -s -D __LOGUS_UPDATE_CHANNEL__=release $^ -o build/$@/$(PROGRAM_NAME)
	@@echo $(TIMESTAMP) > version

experimental: $(EXPERIMENTAL_BUILD_FILES) res.res
	$(CC) $(COMPILE_FLAGS) -s -D __LOGUS_UPDATE_CHANNEL__=experimental $^ -o build/$@/$(PROGRAM_NAME)
	@@echo $(TIMESTAMP) > version_experimental

debug: $(DEBUG_BUILD_FILES)
	$(CC) $(COMPILE_FLAGS) -D __LOGUS_UPDATE_CHANNEL__=debug $^ -o build/$@/$(PROGRAM_NAME)

res.res: res.rc
	windres $< -O coff -o $@

build/release/%.o: $(subst build/release/,,%.cpp)
	@mkdir $(subst /,\,$(@D)) ||:
	$(CC) -MMD $(COMPILE_FLAGS) -D __LOGUS_UPDATE_CHANNEL__=release -c $< -o $@

build/experimental/%.o: $(subst build/experimental/,,%.cpp)
	@mkdir $(subst /,\,$(@D)) ||:
	$(CC) -MMD $(COMPILE_FLAGS) -D __LOGUS_UPDATE_CHANNEL__=experimental -c $< -o $@

build/debug/%.o: $(subst build/debug/,,%.cpp)
	@mkdir $(subst /,\,$(@D)) ||:
	$(CC) -MMD $(COMPILE_FLAGS) -D __LOGUS_UPDATE_CHANNEL__=debug -c $< -o $@

cleanall: cleanrelease cleanexperimental cleandebug

cleanrelease:
	-rmdir /s /q build\release ||:

cleanexperimental:
	-rmdir /s /q build\experimental ||:

cleandebug:
	-rmdir /s /q build\debug ||:

-include $(DEPENDENCIES)