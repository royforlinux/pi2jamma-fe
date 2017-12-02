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

FitRectResult clip(
	const Rect& targetRect,
	const Rect& sourceTargetRect,
	const Rect& sourceRect);

FitRectResult fitRect(
	const Rect& sourceRect,
	const Rect& targetRect,
	CropMode cropMode,
	HorizontalAlignment horizontalAlignment,
	VerticalAlignment verticalAlignment);

}



	




