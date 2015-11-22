#pragma once

#include "core/Types.h"

class Resource
{
public:
	Resource();
	virtual ~Resource();

	void use();
	void load();
	void release();
	void unuse();

	virtual void onLoad();
	virtual void onRelease();

	uint32 getUseCount() const;
	uint32 getLoadCount() const;

private:
	uint32 m_uses;
	uint32 m_loads;
};
