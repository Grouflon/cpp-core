#include "stdafx.h"
#include "core/Locator.h"

uint32 Locator::s_nextIndex = 0u;
std::vector<void*> Locator::s_services;