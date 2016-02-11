#pragma once

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
	void load();
	void loadUse();
	void release();
	void unuse();
	void releaseUnuse();

	virtual void onLoad();
	virtual void onRelease();

	uint32 getUseCount() const;
	uint32 getLoadCount() const;

	bool isLoaded() const;

	Error getError() const;
	const char* getErrorDescription() const;

protected:
	void setError(Error _error, const char* _description = nullptr);

private:
	Error m_error;
	std::string m_errorDescription;
	uint32 m_uses;
	uint32 m_loads;
};
