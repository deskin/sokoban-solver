ifeq ($(origin CC),default)
    CC = clang
endif

OBJDIR = bin
TESTOBJDIR = $(OBJDIR)/test
DEPDIR = $(OBJDIR)/deps
TESTDEPDIR = $(TESTOBJDIR)/deps
SOURCES = sokoban.cpp
TESTSRC = test.cpp test2.cpp
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))
OBJPATHS = $(addprefix $(OBJDIR)/,$(OBJS))
DEPS = $(patsubst %.cpp,%.dep,$(SOURCES))
DEPPATHS = $(addprefix $(DEPDIR)/,$(DEPS))
TESTOBJS = $(patsubst %.cpp,%.o,$(TESTSRC))
TESTOBJPATHS = $(addprefix $(TESTOBJDIR)/,$(TESTOBJS))
TESTDEPS = $(patsubst %.cpp,%.dep,$(TESTSRC))
TESTDEPPATHS = $(addprefix $(TESTDEPDIR)/,$(TESTDEPS))
EXE = sokoban.exe
EXEPATH = $(addprefix $(OBJDIR)/,$(EXE))
TESTEXE = test.exe
TESTEXEPATH = $(addprefix $(OBJDIR)/,$(TESTEXE))
LIBS = -lstdc++
TESTLIBS = -lboost_unit_test_framework-mt

WARNFLAGS ?= -Wall -Werror
OPTFLAGS ?=
STDFLAGS ?= -std=c++11
ALL_CFLAGS = $(CFLAGS) $(WARNFLAGS) $(OPTFLAGS) $(STDFLAGS)

ifeq ($(CC),clang)
    INCLUDES = -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++ -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++/i686-pc-cygwin
endif

all: $(EXEPATH)

.PHONY: test
test: $(TESTEXEPATH)
	$(TESTEXEPATH)

$(EXEPATH): $(OBJPATHS)
	$(CC) $(LDFLAGS) -o $(EXEPATH) $(OBJPATHS) $(LIBS)

$(TESTEXEPATH): $(TESTOBJPATHS)
	$(CC) $(LDFLAGS) -o $@ $(TESTOBJPATHS) $(LIBS) $(TESTLIBS)

$(OBJPATHS): | $(OBJDIR)

$(TESTOBJPATHS): | $(TESTOBJDIR)

$(DEPPATHS): makefile | $(DEPDIR)

$(TESTDEPPATHS): makefile | $(TESTDEPDIR)

$(DEPDIR) $(TESTOBJDIR): | $(OBJDIR)

$(TESTDEPDIR): | $(TESTOBJDIR)

$(OBJDIR) $(DEPDIR) $(TESTOBJDIR) $(TESTDEPDIR):
	mkdir $@

$(OBJDIR)/%.o: %.cpp
	$(CC) $(ALL_CFLAGS) $(INCLUDES) -c -o $@ $<

$(TESTOBJDIR)/%.o: %.cpp
	$(CC) $(ALL_CFLAGS) $(INCLUDES) -c -o $@ $<

$(DEPDIR)/%.dep: %.cpp
	$(CC) $(INCLUDES) -M $< | sed -e "1{s+^\([^:]*\).o:+$(OBJDIR)/\1.o $@:+}" > $@

$(TESTDEPDIR)/%.dep: %.cpp
	$(CC) $(INCLUDES) -M $< | sed -e "1{s+^\([^:]*\).o:+$(TESTOBJDIR)/\1.o $@:+}" > $@

.PHONY: clean
clean:
	-rm -rf $(OBJDIR)/*

include $(DEPPATHS)
include $(TESTDEPPATHS)

