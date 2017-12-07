#pragma once

#include "Pi2Jamma/screens/GameSelectScreen.hpp"
#include "Pi2Jamma/games/Games.hpp"

class GameSelectScreen;

class GamesListModel : public GameSelectScreenModel
{
public:

	GamesListModel(
		Games& games,
		std::string snapFilePath);

private:

	virtual CStr getTitle() override;
	virtual CStr getSnapFilePath(size_t index) override;
	virtual size_t getNumItems() override;
	virtual CStr getItem(size_t index) override;
	virtual void onItemSelected(size_t index) override;

	Games& mGames;
	std::string mSnapFilePath;
};

