#pragma once

#include "core/Application.h"

class ZonkApp
	: public Application
{
public:

	ZonkApp();
	virtual ~ZonkApp();

	virtual void started() override;
	virtual void update(float dt) override;
};
