#include "core/Resource.h"

#include "core/Assert.h"
#include "core/ResourceManager.h"

Resource::Resource()
	: m_uses(0u)
	, m_loads(0u)
{
	m_error = RESOURCE_NOERROR;
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

bool Resource::isLoaded() const
{
	return m_loads > 0;
}

Resource::Error Resource::getError() const
{
	return m_error;
}

const char* Resource::getErrorDescription() const
{
	return m_errorDescription.c_str();
}

void Resource::setError(Error _error, const char* _description)
{
	m_error = _error;
	m_errorDescription = _description;
}
