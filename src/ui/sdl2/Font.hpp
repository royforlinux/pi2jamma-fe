#pragma once

#include "ui/sdl2/sdl2types.hpp"
#include "core/RefCounted.hpp"

class Font final : public RefCounted
{
public:

	Font(std::unique_ptr<TTF_Font> uptSdlFont);

private:

	std::unique_ptr<TTF_Font> muptSdlFont;

friend class Application;	
};