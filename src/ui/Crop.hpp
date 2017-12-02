#pragma once

#include "ui/CropMode.hpp"
#include "ui/HorizontalAlignment.hpp"
#include "ui/Size.hpp"
#include "ui/Rect.hpp"
#include "ui/VerticalAlignment.hpp"

namespace ui
{

Rect fitRect(
	const Size& sourceSize,
	const Rect& targetRect,
	CropMode cropMode,
	HorizontalAlignment horizontalAlignment,
	VerticalAlignment verticalAlignment);

}



	




