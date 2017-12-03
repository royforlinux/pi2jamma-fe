#pragma once

#include "Pi2Jamma/Games.hpp"

#include "core/debug.hpp"
#include "ui/elements/TextList.hpp"

class GamesListModel : public ui::TextListModel
{
public:

	GamesListModel(Games& games);

private:
	virtual size_t getNumItems() const override;
	virtual CStr getItem(size_t index) const override;
	virtual void onSelect(size_t newSelection) override;

	Games& mGames;
};

inline GamesListModel::GamesListModel(Games& games)
	: mGames(games)
{}

inline size_t GamesListModel::getNumItems() const
{
	return mGames.getGameList().size();
}

inline CStr GamesListModel::getItem(size_t index) const
{
	return mGames.getGameList()[index].getDisplayName().c_str();
}

inline void GamesListModel::onSelect(size_t newSelection) {
	
}
