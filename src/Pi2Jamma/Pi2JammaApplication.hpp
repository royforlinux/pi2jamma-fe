#pragma once

#include "Pi2Jamma/Configuration/Configuration.hpp"
#include "Pi2Jamma/Games.hpp"
#include "Pi2Jamma/Theme.hpp"

#include "ui/Application.hpp"
#include "ui/KeyDownEvent.hpp"
#include "ui/RenderContext.hpp"
#include "ui/elements/Element.hpp"


class Pi2JammaApplication : public ui::Application
{

private:
	virtual Result initialize(int argc, const char* argv[]) override;

	virtual void render(ui::RenderContext& renderContext) override;

	virtual void keyDownEvent(const ui::KeyDownEvent& keyDownEvent) override;

	Result loadConfiguration();
	Result setupUi();

	Configuration mConfiguration;
	Games mGames;
	Theme mTheme;

	std::string mFullThemeDir;
	std::string mSnapsDir;

	ref<ui::Element> mrefRootElement;
};
