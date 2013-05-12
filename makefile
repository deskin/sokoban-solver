LINKLIBS=-lstdc++

clang:
clean:
	@rm a.exe
clang -std=c++11 -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++ -I/usr/lib/gcc/i686-pc-cygwin/4.7.2/include/c++/i686-pc-cygwin sokoban.cpp -lstdc++
