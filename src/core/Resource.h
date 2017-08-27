#pragma once

#include <string>
#include <core/Types.h>

class Resource
{
public:
	enum Error
	{
		ERROR_NONE,
		ERROR_LOAD
	};

	Resource();
	virtual ~Resource();

	void use();
	bool load();
	bool loadUse();
	void release();
	void unuse();
	void releaseUnuse();

	virtual void onLoad();
	virtual void onRelease();

	u32 getUseCount() const;
	u32 getLoadCount() const;

	bool isLoaded() const;

	Error getError() const;
	const char* getErrorDescription() const;

protected:
	void setError(Error _error, const char* _description = nullptr);

private:
	Error m_error;
	std::string m_errorDescription;
	u32 m_uses;
	u32 m_loads;
};
