#pragma once

#include "ui/ui.hpp"

class Pi2JammaApplication : public Application
{
private:
	virtual Result initialize() override;

	virtual void render() override;

	virtual void keyDownEvent(const KeyDownEvent& keyDownEvent) override;


	Surface mBackground;
	Surface mTitle;
	Font mFont;
};
