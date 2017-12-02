#include "ui/Crop.hpp"

#include "core/debug.hpp"
#include "ui/Point.hpp"

namespace ui
{

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
	const Size& sourceSize,
	const Rect& targetRect,
	CropMode cropMode,
	HorizontalAlignment horizontalAlignment,
	VerticalAlignment verticalAlignment)
{
	Size resultingSize;

	if(CropMode::AspectFit == cropMode)
	{
		float sourceAspectRatio = sourceSize.getAspectRatio();
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
		resultingSize = sourceSize;
	}

	Rect r =
		getRectForSizeAlignedInRect(
			resultingSize,
			targetRect,
			horizontalAlignment,
			verticalAlignment);

	return FitRectResult(
		r,
		Rect(Point(0,0), sourceSize));
}

}


