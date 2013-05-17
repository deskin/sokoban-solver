ifeq ($(origin CC),default)
    CC = clang
endif

OBJDIR = bin
SOURCES = sokoban.cpp
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))
OBJPATHS = $(addprefix $(OBJDIR)/,$(OBJS))
EXE = sokoban.exe
EXEPATH = $(addprefix $(OBJDIR)/,$(EXE))
LIBS=-lstdc++

ifeq ($(CC),clang)
    INCLUDES = -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++ -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++/i686-pc-cygwin
    CFLAGS = -std=c++11
else ifeq ($(CC),gcc)
    CFLAGS = -std=c++0x
endif

all: $(EXEPATH)

$(EXEPATH): $(OBJPATHS)
	$(CC) $(LDFLAGS) -o $(EXEPATH) $(OBJPATHS) $(LIBS)

$(OBJPATHS): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

.PHONY: clean
clean:
	-rm -f $(OBJDIR)/*
