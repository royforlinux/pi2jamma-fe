#pragma once

#include "ui/device/sdl2/Point.hpp"
#include "ui/device/sdl2/Size.hpp"

class Rect
{
public:
	Rect();
	Rect(UnitType x, UnitType y, UnitType w, UnitType h);

	UnitType getX() const;
	UnitType getY() const;
	UnitType getWidth() const;
	UnitType getHeight() const;
	UnitType getYCenter() const;

	Size getSize() const;

	Point getPosition() const;
	void setPosition(const Point& position);

	const SDL_Rect* getSdlRect() const;
	
private:
	SDL_Rect mSdlRect;

};

inline Rect::Rect(UnitType x, UnitType y, UnitType w, UnitType h)
	: mSdlRect({x,y,w,h})
{

}

inline Rect::Rect()
	: mSdlRect({0,0,0,0})
{
}

inline UnitType Rect::getX() const
{
	return mSdlRect.x;
}

inline UnitType Rect::getY() const
{
	return mSdlRect.y;
}

inline UnitType Rect::getWidth() const
{
	return mSdlRect.w;
}

inline UnitType Rect::getHeight() const
{
	return mSdlRect.h;
}

inline UnitType Rect::getYCenter() const
{
	return mSdlRect.y + (mSdlRect.h / 2);
}

inline Point Rect::getPosition() const
{
	return Point(getX(), getY());
}

inline void Rect::setPosition(const Point& position)
{
	mSdlRect.x = position.getX();
	mSdlRect.y = position.getY();
}

inline const SDL_Rect* Rect::getSdlRect() const
{
	return &mSdlRect;
}

inline Size Rect::getSize() const {
	return Size(mSdlRect.w, mSdlRect.h);
}
