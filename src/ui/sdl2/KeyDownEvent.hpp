#pragma once

#include "debug.hpp"

enum class Key {
	DownArrow = SDLK_DOWN
	UpArrow = SDLK_UP
};

class KeyDownEvent
{
public:
	KeyDownEvent(const SDL_Event& event);

	Key getKey() const;

private:
	const SDL_Event &mSdlEvent;
};

inline KeyDownEvent::KeyDownEvent(const SDL_Event& event)
	: mSdlEvent(event)
{
	LogFmt("KeyDown scancode: 0x%x\n", mSdlEvent.key.keysym.sym);
}

inline Key KeyDownEvent::getKey() const
{
	return static_cast<Key>(mSdlEvent.key.keysym.sym);
}