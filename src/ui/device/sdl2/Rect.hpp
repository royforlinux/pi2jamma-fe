#pragma once

#include "ui/device/sdl2/Point.hpp"
#include "ui/device/sdl2/Size.hpp"

class Rect
{
public:
	Rect();
	Rect(UnitType x, UnitType y, UnitType w, UnitType h);

	UnitType getX() const;
	void setX(UnitType x);

	UnitType getY() const;
	void setY(UnitType y);

	UnitType getWidth() const;
	void setWidth(UnitType width);

	UnitType getHeight() const;
	void setHeight(UnitType height);

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

inline void Rect::setX(UnitType x) 
{
	mSdlRect.x = x;
}

inline UnitType Rect::getY() const
{
	return mSdlRect.y;
}

inline void Rect::setY(UnitType y)
{
	mSdlRect.y = y;
}

inline UnitType Rect::getWidth() const
{
	return mSdlRect.w;
}

inline void Rect::setWidth(UnitType w) 
{
	mSdlRect.w = w;
}

inline UnitType Rect::getHeight() const
{
	return mSdlRect.h;
}

inline void Rect::setHeight(UnitType height)
{
	mSdlRect.h = height;
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
