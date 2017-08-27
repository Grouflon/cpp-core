#pragma once

#ifdef _MSC_VER
#include <intrin.h>
#define DEBUG_BREAK __debugbreak()
#else
#define DEBUG_BREAK raise(SIGTRAP)
#endif

#ifdef ASSERT
#undef ASSERT
#endif

#ifdef DEBUG
#define ASSERT(cond) if (!(cond)) DEBUG_BREAK;
#else
#define ASSERT(cond)
#endif
