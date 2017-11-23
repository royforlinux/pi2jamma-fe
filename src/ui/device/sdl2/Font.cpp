#include "ui/device/sdl2/Font.hpp"

Font::Font(std::unique_ptr<TTF_Font> uptSdlFont)
	: muptSdlFont(std::move(uptSdlFont))
{
}