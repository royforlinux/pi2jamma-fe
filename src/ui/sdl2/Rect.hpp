#pragma once

#include "ui/sdl2/Point.hpp"

class Rect
{
public:
	Rect();
	Rect(UnitType x, UnitType y, UnitType w, UnitType h);

	UnitType getX() const;
	UnitType getY() const;
	UnitType getWidth() const;
	UnitType getHeight() const;

	Point getPosition() const;
	void setPosition(const Point& position);
	
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

inline Point Rect::getPosition() const
{
	return Point(getX(), getY());
}

inline void Rect::setPosition(const Point& position)
{
	mSdlRect.x = position.getX();
	mSdlRect.y = position.getY();
}
