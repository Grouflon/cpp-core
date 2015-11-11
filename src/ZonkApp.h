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
	virtual void render() override;

	virtual void onKeyEvent(int key, int scancode, int action, int mods) override;
	virtual void onCharEvent(char c) override;
};
