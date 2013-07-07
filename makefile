ifeq ($(origin CC),default)
    CC = clang
endif

OBJDIR = bin
TESTOBJDIR = $(OBJDIR)/test
TESTSRCDIR = test
DEPDIR = $(OBJDIR)/deps
TESTDEPDIR = $(TESTOBJDIR)/deps
ALL_SRC = $(wildcard *.cpp)
MAIN_SRC = sokoban.cpp
SOURCES = $(filter-out $(MAIN_SRC),$(ALL_SRC))
TESTSRC = $(wildcard $(TESTSRCDIR)/*.cpp)
ALL_OBJS = $(patsubst %.cpp,%.o,$(ALL_SRC))
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))
ALL_OBJPATHS = $(addprefix $(OBJDIR)/,$(ALL_OBJS))
OBJPATHS = $(addprefix $(OBJDIR)/,$(OBJS))
DEPS = $(patsubst %.cpp,%.dep,$(ALL_SRC))
DEPPATHS = $(addprefix $(DEPDIR)/,$(DEPS))
TESTOBJS = $(patsubst %.cpp,%.o,$(notdir $(TESTSRC)))
TESTOBJPATHS = $(addprefix $(TESTOBJDIR)/,$(TESTOBJS))
TESTDEPS = $(patsubst %.cpp,%.dep,$(notdir $(TESTSRC)))
TESTDEPPATHS = $(addprefix $(TESTDEPDIR)/,$(TESTDEPS))
EXE = sokoban.exe
EXEPATH = $(addprefix $(OBJDIR)/,$(EXE))
TESTEXE = test.exe
TESTEXEPATH = $(addprefix $(OBJDIR)/,$(TESTEXE))
LIBS = -lstdc++
TESTLIBS = -lboost_unit_test_framework-mt

INCLUDES = -iquote include
WARNFLAGS ?= -Wall -Werror
OPTFLAGS ?=
LDFLAGS ?=
ALL_LDFLAGS = $(LDFLAGS) $(OPTFLAGS) $(WARNFLAGS)
STDFLAGS ?= -std=c++11
ALL_CFLAGS = $(CFLAGS) $(WARNFLAGS) $(OPTFLAGS) $(STDFLAGS)

ifeq ($(CC),clang)
    INCLUDES += -I/usr/lib/gcc/i686-pc-cygwin/4.7.3/include -I/usr/lib/gcc/i686-pc-cygwin/4.7.3/include/c++ -I/usr/lib/gcc/i686-pc-cygwin/4.7.3/include/c++/i686-pc-cygwin
endif

all: $(EXEPATH)

.PHONY: test
test: $(TESTEXEPATH)
	$(TESTEXEPATH)

$(EXEPATH): $(ALL_OBJPATHS)
	$(CC) $(ALL_LDFLAGS) -o $@ $(ALL_OBJPATHS) $(LIBS)

$(TESTEXEPATH): $(OBJPATHS) $(TESTOBJPATHS)
	$(CC) $(ALL_LDFLAGS) -o $@ $(TESTOBJPATHS) $(OBJPATHS) $(LIBS) $(TESTLIBS)

$(ALL_OBJPATHS): | $(OBJDIR)

$(TESTOBJPATHS): | $(TESTOBJDIR)

$(DEPPATHS): makefile | $(DEPDIR)

$(TESTDEPPATHS): makefile | $(TESTDEPDIR)

$(DEPDIR) $(TESTOBJDIR): | $(OBJDIR)

$(TESTDEPDIR): | $(TESTOBJDIR)

$(OBJDIR) $(DEPDIR) $(TESTOBJDIR) $(TESTDEPDIR):
	mkdir $@

$(OBJDIR)/%.o: %.cpp
	$(CC) $(ALL_CFLAGS) $(INCLUDES) -c -o $@ $<

$(TESTOBJDIR)/%.o: $(TESTSRCDIR)/%.cpp
	$(CC) $(ALL_CFLAGS) $(INCLUDES) -c -o $@ $<

$(DEPDIR)/%.dep: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -M $< | sed -e "1{s+^\([^:]*\)[.]o:+$(OBJDIR)/\1.o $@:+}" > $@

$(TESTDEPDIR)/%.dep: $(TESTSRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -M $< | sed -e "1{s+^\([^:]*\)[.]o:+$(TESTOBJDIR)/\1.o $@:+}" > $@

.PHONY: clean
clean:
	-rm -rf $(OBJDIR)/*

include $(DEPPATHS)
include $(TESTDEPPATHS)

