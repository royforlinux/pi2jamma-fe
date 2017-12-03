#include "Pi2Jamma/screens/GamesListModel.hpp"

#include "Pi2Jamma/screens/GameSelectScreen.hpp"

GamesListModel::GamesListModel(
	GameSelectScreen& gameSelectScreen)
	: mGameSelectScreen(gameSelectScreen)
{}

size_t GamesListModel::getNumItems() const
{
	return mGameSelectScreen.getGames().getGameList().size();
}

CStr GamesListModel::getItem(size_t index) const
{
	return
		mGameSelectScreen
			.getGames()
				.getGameList()[index]
					.getDisplayName().c_str();
}

void GamesListModel::onSelect(size_t newSelection) {
	mGameSelectScreen.launchGame(
		mGameSelectScreen
			.getGames()
				.getGameList()[newSelection]);
}