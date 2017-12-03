#pragma once

#include "ui/elements/Label.hpp"
#include "ui/elements/Image.hpp"
#include "ui/elements/TextList.hpp"

#include "Pi2Jamma/Pi2JammaApplication.hpp"
#include "Pi2Jamma/screens/GamesListModel.hpp"

class GameSelectScreen : public ui::Element
{
public:
	GameSelectScreen(
		Pi2JammaApplication& application,
		Games& games,
		CStr fullThemeDir,
		std::string snapsDir);

private:
	
	Pi2JammaApplication& mApplication;
	Games mGames;
	Theme mTheme;
	std::string mSnapsDir;

	GamesListModel mGamesListModel;

	ref<ui::Font> mrefFont;

	ref<ui::Image> mrefBackgroundImage;
	ref<ui::Label> mrefTitle;
	ref<ui::TextList> mrefTextList;
	ref<ui::Image> mrefSnapsImage;
};