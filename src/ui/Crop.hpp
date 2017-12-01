#pragma once

#include "ui/device/UiDevice.hpp"
#include "ui/HorizontalAlignment.hpp"
#include "ui/VerticalAlignment.hpp"
#include "ui/CropMode.hpp"

namespace ui
{

struct CropResult {
	Rect sourceRect;
	Rect targetRect;
};

CropResult crop(
	Rect& targetOut,
	Rect& sourceOut,
	const Rect& target,
	const Rect& source,
	HorizontalAlignment horizontalAlignment,
	VerticalAlignment verticalAlignment,
	CropMode cropMode);



	




