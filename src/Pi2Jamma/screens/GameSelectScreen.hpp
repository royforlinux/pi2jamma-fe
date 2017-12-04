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
		const Games& games,
		CStr fullThemeDir,
		std::string snapsDir);

	void launchGame(const Game& game);
	const Games& getGames();

	void showSnapForGame(const Game& game);
private:
	
	Pi2JammaApplication& mApplication;
	const Games& mGames;
	Theme mTheme;
	std::string mSnapsDir;

	GamesListModel mGamesListModel;

	ref<ui::Font> mrefFont;

	ref<ui::Image> mrefBackgroundImage;
	ref<ui::Label> mrefTitle;
	ref<ui::TextList> mrefTextList;
	ref<ui::Image> mrefSnapsImage;
};

inline const Games& GameSelectScreen::getGames()
{
	return mGames;
}
