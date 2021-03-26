CC						 = g++
TIMESTAMP				:= $(shell get_timestamp)
COMPILE_FLAGS			 = -g -Os -std=c++17 -I src/common -Wall -Wno-sign-compare -Wno-type-limits -Wno-maybe-uninitialized -Wno-comment
PROGRAM_NAME			 = Logus
SOURCE_FILES			:= $(patsubst %.cpp,%.o,$(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp))
VER_DEPENDENCIES_DUMMY   = $(SOURCE_FILES:.o=.cpp)
DEPENDENCIES			 = $(subst src/,build/release/src/,$(SOURCE_FILES:.o=.d))
DEPENDENCIES			+= $(subst src/,build/experimental/src/,$(SOURCE_FILES:.o=.d))
RELEASE_BUILD_FILES		 = $(addprefix build/release/,$(subst src/common/ver.o,,$(SOURCE_FILES)))
EXPERIMENTAL_BUILD_FILES = $(addprefix build/experimental/,$(subst src/common/ver.o,,$(SOURCE_FILES)))
SHELL=cmd

default: release

all: release experimental debug

release: $(RELEASE_BUILD_FILES) res.res
	$(CC) $(COMPILE_FLAGS) -D __LOGUS_BUILD_TYPE__=\"$@\" -D __LOGUS_BUILD_TIMESTAMP__=$(TIMESTAMP) -c src/common/ver.cpp -o build/$@/src/common/ver.o
	$(CC) $(COMPILE_FLAGS) -s $^ build/$@/src/common/ver.o -o $(PROGRAM_NAME)
	@@echo $(TIMESTAMP) > version

experimental: $(EXPERIMENTAL_BUILD_FILES) res.res
	$(CC) $(COMPILE_FLAGS) -D __LOGUS_BUILD_TYPE__=\"$@\" -D __LOGUS_BUILD_TIMESTAMP__=$(TIMESTAMP) -c src/common/ver.cpp -o build/$@/src/common/ver.o
	$(CC) $(COMPILE_FLAGS) -s $^ build/$@/src/common/ver.o -o $(PROGRAM_NAME)
	@@echo $(TIMESTAMP) > version_experimental

debug: $(EXPERIMENTAL_BUILD_FILES)
	$(CC) $(COMPILE_FLAGS) -D __LOGUS_BUILD_TYPE__=\"$@\" -D __LOGUS_BUILD_TIMESTAMP__=$(TIMESTAMP) -c src/common/ver.cpp -o build/$@/src/common/ver.o
	$(CC) $(COMPILE_FLAGS) $^ build/$@/src/common/ver.o -o build/$@/$(PROGRAM_NAME)

res.res: res.rc
	windres $< -O coff -o $@

build/release/%.o: $(subst build/release/,,%.cpp)
	@mkdir $(subst /,\,$(@D)) ||:
	$(CC) -MMD $(COMPILE_FLAGS) -c $< -o $@

build/experimental/%.o: $(subst build/experimental/,,%.cpp)
	@mkdir $(subst /,\,$(@D)) ||:
	$(CC) -MMD $(COMPILE_FLAGS) -c $< -o $@

build/debug/%.o: $(subst build/debug/,,%.cpp)
	@mkdir $(subst /,\,$(@D)) ||:
	$(CC) -MMD $(COMPILE_FLAGS) -c $< -o $@

cleanall: cleanrelease cleanexperimental cleandebug

cleanrelease:
	-rmdir /s /q build\release ||:

cleanexperimental:
	-rmdir /s /q build\experimental ||:

cleandebug:
	-rmdir /s /q build\debug ||:

-include $(DEPENDENCIES)