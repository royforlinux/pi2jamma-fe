#pragma once

#include "Pi2Jamma/Configuration/Configuration.hpp"

#include "ui/Application.hpp"
#include "ui/KeyDownEvent.hpp"
#include "ui/elements/Label.hpp"
#include "ui/elements/Image.hpp"
#include "ui/elements/List.hpp"

class Pi2JammaApplication : public ui::Application
{
private:
	virtual Result initialize(int argc, const char* argv[]) override;

	virtual void render() override;

	virtual void keyDownEvent(const ui::KeyDownEvent& keyDownEvent) override;

	Configuration mConfiguration;
	
	ref<ui::Image> mrefBackground;
	ref<ui::Label> mrefTitle;
	ref<ui::List> mrefList;

	ref<ui::Font> mrefFont;
};
