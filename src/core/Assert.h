#pragma once

#include <intrin.h>

#ifdef ASSERT
#undef ASSERT
#endif

#define ASSERT(cond) if (!(cond)) __debugbreak();
