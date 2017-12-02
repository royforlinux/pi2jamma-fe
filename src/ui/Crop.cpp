#include "ui/Crop.hpp"

#include "core/debug.hpp"
#include "ui/Point.hpp"

namespace ui
{

FitRectResult clip(
	const Rect& targetRect,
	const Rect& sourceTargetRect,
	const Rect& sourceRect) {

	auto targetWidth = targetRect.getWidth();
	auto sourceTargetWidth = sourceTargetRect.getWidth();

	Rect sourceRectOut = sourceRect;
	Rect targetRectOut = sourceTargetRect;

	if(sourceTargetWidth > targetWidth)
	{
		float diffPercent =
			static_cast<float>(targetWidth) /
			static_cast<float>(sourceTargetWidth);

		targetRectOut.setX(targetRect.getX());
		targetRectOut.setWidth(targetRect.getWidth());
		UnitType sourceWidth =
			static_cast<UnitType>(diffPercent * sourceRect.getWidth());
		UnitType diff = sourceRect.getWidth() - sourceWidth;
		sourceRectOut.setX(
			sourceRect.getX() + diff / 2 );
		sourceRectOut.setWidth(sourceWidth);
	}

	return FitRectResult(
		targetRectOut,
		sourceRectOut );
}

Rect getRectForSizeAlignedInRect(
	const Size& sourceSize,
	const Rect& targetRect,
	HorizontalAlignment horizontalAlignment,
	VerticalAlignment verticalAlignment)
{
	Rect rect;
	rect.setSize(sourceSize);

	if(HorizontalAlignment::Center == horizontalAlignment)
	{
		rect.setX(targetRect.getX() + (targetRect.getWidth()-rect.getWidth())/2);
	}
	else if(HorizontalAlignment::Left == horizontalAlignment)
	{
		rect.setX(targetRect.getX());
	}
	else if(HorizontalAlignment::Right == horizontalAlignment)
	{
		rect.setX(targetRect.getRightExclusive() - sourceSize.getWidth());
	} 

	if(VerticalAlignment::Center == verticalAlignment)
	{
		rect.setY(targetRect.getY() + (targetRect.getHeight() - rect.getHeight()) / 2);
	}
	else if(VerticalAlignment::Top == verticalAlignment)
	{
		rect.setY(targetRect.getY());
	}
	else if(VerticalAlignment::Bottom == verticalAlignment)
	{
		rect.setY(targetRect.getBottomExclusive() - sourceSize.getHeight());
	}

	return rect;
}

FitRectResult fitRect(
	const Rect& sourceRect,
	const Rect& targetRect,
	CropMode cropMode,
	HorizontalAlignment horizontalAlignment,
	VerticalAlignment verticalAlignment)
{
	Size resultingSize;

	if(CropMode::AspectFit == cropMode)
	{
		float sourceAspectRatio = sourceRect.getAspectRatio();
		float rectToFitAspectRatio = targetRect.getAspectRatio();

		if(rectToFitAspectRatio < sourceAspectRatio)
		{
			resultingSize.setWidth(targetRect.getWidth());
			resultingSize.setHeight(resultingSize.getWidth() / sourceAspectRatio);
		}
		else
		{
			resultingSize.setHeight(targetRect.getHeight());
			resultingSize.setWidth(resultingSize.getHeight() * sourceAspectRatio);
		}
	}
	else if(CropMode::AspectFill == cropMode)
	{
		ASSERTMSG(false, "CropMode::AspectFill not implemented");
	}
	else if(CropMode::Stretch == cropMode)
	{
		resultingSize = targetRect.getSize();
	}
	else if(CropMode::None == cropMode)
	{
		resultingSize = sourceRect.getSize();
	}

	Rect sourceTargetRect =
		getRectForSizeAlignedInRect(
			resultingSize,
			targetRect,
			horizontalAlignment,
			verticalAlignment);

	auto result = clip(targetRect, sourceTargetRect, sourceRect);

	return result;
}

}

