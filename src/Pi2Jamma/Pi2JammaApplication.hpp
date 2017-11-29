#pragma once

#include "Pi2Jamma/Configuration.hpp"

#include "ui/elements/Label.hpp"
#include "ui/elements/Image.hpp"
#include "ui/elements/List.hpp"

class Pi2JammaApplication : public Application
{
private:
	virtual Result initialize(int argc, const char* argv[]) override;

	virtual void render() override;

	virtual void keyDownEvent(const KeyDownEvent& keyDownEvent) override;

	Configuration mConfiguration;
	
	ref<Image> mrefBackground;
	ref<Label> mrefTitle;
	ref<List> mrefList;

	ref<Font> mrefFont;
};
