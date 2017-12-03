#include "Pi2Jamma/screens/GameSelectScreen.hpp"
#include "ui/Point.hpp"
#include "core/file/FilePath.hpp"
#include "core/serialize/json/JsonSerialize.hpp"

GameSelectScreen::GameSelectScreen(
	Pi2JammaApplication& application,
	const Games& games,
	CStr fullThemeDir,
	std::string snapsDir)
	: ui::Element(
		nullptr,
		ui::Rect(
			ui::Point(0,0),
			application.getScreenSize()))
	, mApplication(application)
	, mGames(games)
	, mSnapsDir(std::move(snapsDir))
	, mGamesListModel(*this)
{
	std::string configFilePath =
		joinPath(fullThemeDir, "config.txt");

	Result result = loadJson(mTheme, configFilePath.c_str());
	result.catastrophic();

	mrefBackgroundImage =
		make_ref<ui::Image>(
			this,
			getRect(),
			joinPath(fullThemeDir, "background.png"));

	mrefSnapsImage =
		make_ref<ui::Image>(
			this,
			mTheme.getSnapsRect(),
			gEmptyString);

	result =
		application.loadFont(
			mrefFont,
			mTheme.getMenuTextSize(),
			joinPath(fullThemeDir, mTheme.getFontFilePath()));
	result.catastrophic();

	mrefTitle =
		make_ref<ui::Label>(
			this,
			mTheme.getTitleRect(),
			mrefFont,
			mTheme.getTitleTextColor(),
			"Title",
			mTheme.getTitleAlignment());

	mrefTextList =
		make_ref<ui::TextList>(
			mGamesListModel,
			this,
			mTheme.getMenuRect(),
			mrefFont,
			mTheme.getMenuTextColor(),
			mTheme.getMenuTextHighlightColor(),
			mTheme.getMenuTextSize());
}

void GameSelectScreen::launchGame(const Game& game)
{
	LogFmt("Select game!: %s\n", game.getDisplayName().c_str());

}

