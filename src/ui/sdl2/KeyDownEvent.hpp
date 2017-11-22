#pragma once

class KeyDownEvent
{
public:
	KeyDownEvent(const SDL_Event& event);

private:
	const SDL_Event &mSdlEvent;
};

inline KeyDownEvent::KeyDownEvent(const SDL_Event& event)
	: mSdlEvent(event)
{
}