#pragma once

#include "ui/sdl2/sdl2types.hpp"

class Font final
{
public:
	Font() = default;

private:
	Font(std::unique_ptr<TTF_Font> uptSdlFont);

	std::unique_ptr<TTF_Font> muptSdlFont;

friend class Application;	
};