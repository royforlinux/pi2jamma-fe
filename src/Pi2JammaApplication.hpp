#pragma once

#include "ui/device/ui.hpp"
#include "ui/elements/Label.hpp"
#include "ui/elements/Image.hpp"
#include "ui/elements/List.hpp"

class Pi2JammaApplication : public Application
{
private:
	virtual Result initialize() override;

	virtual void render() override;

	virtual void keyDownEvent(const KeyDownEvent& keyDownEvent) override;


	ref<Image> mrefBackground;
	ref<Label> mrefTitle;
	ref<List> mrefList;

	ref<Font> mrefFont;
};
