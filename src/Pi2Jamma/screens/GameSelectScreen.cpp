#include "Pi2Jamma/screens/GameSelectScreen.hpp"

#include "Pi2Jamma/Pi2JammaApplication.hpp"

#include "ui/Point.hpp"
#include "ui/Application.hpp"

#include "core/file/FilePath.hpp"
#include "core/serialize/json/JsonSerialize.hpp"

GameSelectScreen::TextListModel::TextListModel(
	GameSelectScreen& gameSelectScreen)
	: mGameSelectScreen(gameSelectScreen)
{
}

size_t GameSelectScreen::TextListModel::getNumItems() const
{
	return mGameSelectScreen.mrefModel->getNumItems();
}

CStr GameSelectScreen::TextListModel::getItem(size_t index) const
{
	return mGameSelectScreen.mrefModel->getItem(index);
}

void GameSelectScreen::TextListModel::onItemHighlighted(size_t index)
{
	return
		mGameSelectScreen.showSnap(
			mGameSelectScreen.mrefModel->getSnapFilePath(index));
}

void GameSelectScreen::TextListModel::onItemSelected(size_t index)
{
	return mGameSelectScreen.mrefModel->onItemSelected(index);
}	

GameSelectScreen::GameSelectScreen(
	ui::Element* pParent,
	const ui::Rect& rect,
	ref<GameSelectScreenModel> refModel,
	CStr fullThemeDirectoryPath)
	: ui::Element(
		pParent,
		rect)
	, mrefModel(std::move(refModel))
	, mrefTextListModel(make_ref<TextListModel>(*this))
{
	std::string configFilePath =
		joinPath(fullThemeDirectoryPath, "config.txt");

	Result result = loadJson(mTheme, configFilePath.c_str());
	result.catastrophic();

	mrefBackgroundImage =
		make_ref<ui::Image>(
			this,
			getRect(),
			joinPath(fullThemeDirectoryPath, "background.png"));

	mrefSnapsImage =
		make_ref<ui::Image>(
			this,
			mTheme.getSnapsRect(),
			gEmptyString);

	result =
		ui::Application::get().loadFont(
			mrefFont,
			mTheme.getMenuTextSize(),
			joinPath(fullThemeDirectoryPath, mTheme.getFontFilePath()));
	result.catastrophic();

	mrefTitle =
		make_ref<ui::Label>(
			this,
			mTheme.getTitleRect(),
			mrefFont,
			mTheme.getTitleTextColor(),
			std::string(mrefModel->getTitle().c_str()),
			mTheme.getTitleAlignment());

	mrefTextList =
		make_ref<ui::TextList>(
			this,
			mTheme.getMenuRect(),
			mrefTextListModel,			
			mrefFont,
			mTheme.getMenuTextColor(),
			mTheme.getMenuTextHighlightColor(),
			mTheme.getMenuTextSize());
}

void GameSelectScreen::showSnap(CStr snapFilePath)
{
	if(snapFilePath.size() <= 0)
	{
		mrefSnapsImage->setSurface(nullptr);
		return;
	}

	mrefSnapsImage->loadFromFile(snapFilePath);
}

