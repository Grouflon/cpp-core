#include "stdafx.h"
#include "core/Resource.h"

#include "core/ResourceManager.h"

Resource::Resource()
	: m_uses(0u)
	, m_loads(0u)
{
	g_resourceManager.registerResource(this);
}

Resource::~Resource()
{
	ASSERT(m_uses == 0 && m_loads == 0) // if not, the resource is not properly used
}

void Resource::use()
{
	++m_uses;
}

void Resource::load()
{
	if (m_loads == 0)
	{
		onLoad();
	}

	++m_loads;
}

void Resource::release()
{
	if (m_loads == 0)
	{
		ASSERT(false) // excess release
		return;
	}

	--m_loads;

	if (m_loads == 0)
	{
		onRelease();
	}
}

void Resource::unuse()
{
	if (m_uses == 0)
	{
		ASSERT(false) // excess unuse
		return;
	}

	--m_uses;
}

void Resource::onLoad()
{
}

void Resource::onRelease()
{
}

uint32 Resource::getUseCount() const
{
	return m_uses;
}

uint32 Resource::getLoadCount() const
{
	return m_loads;
}