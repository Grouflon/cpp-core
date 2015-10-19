#pragma once

#include "core/Application.h"

class SandboxApp
	: public Application
{
public:

	SandboxApp();
	virtual ~SandboxApp();

	void onStart() override;
	void onUpdate(float dt) override;
	void onRender(RenderContext* ctx) override;
	void onStop() override;
};
