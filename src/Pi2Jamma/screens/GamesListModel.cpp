#include "Pi2Jamma/screens/GamesListModel.hpp"

#include "Pi2Jamma/screens/GameSelectScreen.hpp"
#include "core/file/FilePath.hpp"

GamesListModel::GamesListModel(
	Games& games,
	std::string snapFilePath)
	: mGames(games)
	, mSnapFilePath(std::move(snapFilePath))
{
}

CStr GamesListModel::getTitle()
{
	return "Games";
}

size_t GamesListModel::getNumItems()
{
	return mGames.getGameList().size();
}

CStr GamesListModel::getItem(size_t index)
{
	return
		mGames
			.getGameList()[index]
				.getDisplayName().c_str();
}

CStr GamesListModel::getSnapFilePath(size_t index)
{
	return
		joinPath(
			mSnapFilePath,
			mGames.getGameList()[index].getSnapName());
}

void GamesListModel::onItemSelected(size_t newSelection)
{
	/* mGameSelectScreen.launchGame(
		mGames.
			.getGameList()[newSelection]); */
}