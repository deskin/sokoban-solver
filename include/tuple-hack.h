#ifndef SOKOBAN_TUPLE_HACK_H_
#define SOKOBAN_TUPLE_HACK_H_

#ifndef __GXX_EXPERIMENTAL_CXX0X__
#define __GXX_EXPERIMENTAL_CXX0X__ 1
#define SOKOBAN_GXX_EXPERIMENTAL_CXX0X_DEFINED_
#endif

#include <tuple>

#ifdef SOKOBAN_GXX_EXPERIMENTAL_CXX0X_DEFINED_
#undef __GXX_EXPERIMENTAL_CXX0X__
#undef SOKOBAN_GXX_EXPERIMENTAL_CXX0X_DEFINED_
#endif

#endif // SOKOBAN_TUPLE_HACK_H_
