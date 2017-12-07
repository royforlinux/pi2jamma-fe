#pragma once

#include "ui/elements/Label.hpp"
#include "ui/elements/Image.hpp"
#include "ui/elements/TextList.hpp"

#include "Pi2Jamma/Theme.hpp"

class Pi2JammaApplication;

class GameSelectScreenModel : public RefCounted
{
	public:
		virtual CStr getTitle() = 0;
		virtual CStr getSnapFilePath(size_t index) = 0;
		virtual size_t getNumItems() = 0;
		virtual CStr getItem(size_t index) = 0;
		virtual void onItemSelected(size_t index) = 0;
};

class GameSelectScreen : public ui::Element
{
public:
	GameSelectScreen(
		ui::Element* pParent,
		const ui::Rect& rect,
		ref<GameSelectScreenModel> refModel,
		CStr fullThemeDirectoryPath);

private:

	class TextListModel final : public ui::TextListModel
	{
	public:
		TextListModel(GameSelectScreen& gameSelectScreen);

		virtual size_t getNumItems() const override;
		virtual CStr getItem(size_t index) const override;
		virtual void onItemHighlighted(size_t newSelection) override;
		virtual void onItemSelected(size_t newSelection) override;

	private:
		GameSelectScreen& mGameSelectScreen;
	};
	
	void showSnap(CStr filePath);

	ref<GameSelectScreenModel> mrefModel;
	ref<TextListModel> mrefTextListModel;
	Theme mTheme;

	ref<ui::Font> mrefFont;

	ref<ui::Image> mrefBackgroundImage;
	ref<ui::Label> mrefTitle;
	ref<ui::TextList> mrefTextList;
	ref<ui::Image> mrefSnapsImage;
};


