#pragma once

#include <intrin.h>

#ifdef ASSERT
#undef ASSERT
#endif

#ifdef _DEBUG
#define ASSERT(cond) if (!(cond)) __debugbreak();
#else
#define ASSERT(cond)
#endif
