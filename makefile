ifeq ($(origin CC),default)
    CC = clang
endif

SOURCES = sokoban.cpp
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))
EXE = sokoban.exe
LIBS=-lstdc++

ifeq ($(CC),clang)
    INCLUDES = -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++ -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++/i686-pc-cygwin
    CFLAGS = -std=c++11
else ifeq ($(CC),gcc)
    CFLAGS = -std=c++0x
endif

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXE) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

.PHONY: clean
clean:
	-rm -f $(EXE) $(OBJS)
