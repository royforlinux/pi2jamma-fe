#pragma once

#include "ui/sdl2/sdl2types.hpp"

class Size
{
public:
	Size(UnitType width = 0, UnitType height = 0);
	
	UnitType getWidth() const;
	UnitType getHeight() const;

private:
	UnitType mWidth;
	UnitType mHeight;
};

inline Size::Size(UnitType width, UnitType height)
	: mWidth(width)
	, mHeight(height)
{
}

inline UnitType Size::getWidth() const
{
	return mWidth;
}

inline UnitType Size::getHeight() const
{
	return mHeight;
}