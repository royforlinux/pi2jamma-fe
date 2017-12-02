#pragma once

#include "core/Property.hpp"
#include "ui/CropMode.hpp"
#include "ui/HorizontalAlignment.hpp"
#include "ui/Size.hpp"
#include "ui/Rect.hpp"
#include "ui/VerticalAlignment.hpp"

namespace ui
{

struct FitRectResult
{
	FitRectResult(
		const Rect& targetRect,
		const Rect& sourceRect)
		: mTargetRect(targetRect)
		, mSourceRect(sourceRect) {}
	
	PROPERTY(Rect, TargetRect);
	PROPERTY(Rect, SourceRect);
};

FitRectResult fitRect(
	const Size& sourceSize,
	const Rect& targetRect,
	CropMode cropMode,
	HorizontalAlignment horizontalAlignment,
	VerticalAlignment verticalAlignment);

}



	




