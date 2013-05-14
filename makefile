CC ?= clang
SOURCES = sokoban.cpp
EXE = sokoban.exe
LINKLIBS=-lstdc++

ifeq ($(CC),clang)
    INCLUDES = -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++ -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++/i686-pc-cygwin
    CFLAGS = -std=c++11
else ifeq ($(CC),gcc)
    CFLAGS = -std=c++0x
endif

all: $(EXE)

$(EXE): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXE) $(SOURCES) $(LINKLIBS)

.PHONY: clean
clean:
	-rm -f $(EXE)
#clang -std=c++11 -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++ -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++/i686-pc-cygwin sokoban.cpp -lstdc++
