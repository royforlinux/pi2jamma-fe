#pragma once

#include "ui/ui.hpp"
#include "ui/Label.hpp"
#include "ui/Image.hpp"
#include "ui/List.hpp"

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
