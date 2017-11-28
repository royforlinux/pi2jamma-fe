#pragma once

#include "ui/device/sdl2/Application.hpp"

#include "core/serialize/Serializer.hpp"

using RenderContext = Application;

namespace ui
{
	void initialize();
}

template<>
class Serializer<Color>
{
	Result load( Color& color, const Json& json);
	Result save( const Color& color, Json& json);	
};