#pragma once

#include "core/Application.h"

class BlonkApp
	: public Application
{
public:
	BlonkApp();
	virtual ~BlonkApp();

	virtual void started() override;
	virtual void render() override;
};
