#pragma once

#include "ui/ui.hpp"
#include "ui/Label.hpp"
#include "ui/Image.hpp"

class Pi2JammaApplication : public Application
{
private:
	virtual Result initialize() override;

	virtual void render() override;

	virtual void keyDownEvent(const KeyDownEvent& keyDownEvent) override;


	ref<Image> mrefBackground;
	ref<Label> mrefTitle;

	Font mFont;
};
