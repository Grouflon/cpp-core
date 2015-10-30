#pragma once

#include "core/Application.h"

class SandboxApp
	: public Application
{
public:

	SandboxApp();
	virtual ~SandboxApp();

	virtual void started() override;
	virtual void update(float dt) override;
	virtual void render() override;
	virtual void stopped() override;
};
