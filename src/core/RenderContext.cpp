#include "stdafx.h"
#include "core/RenderContext.h"

RenderContext::RenderContext()
{
}

RenderContext::~RenderContext()
{
}

void RenderContext::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}