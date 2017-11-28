#pragma once

#include "ui/device/sdl2/Application.hpp"

#include "core/meta/Meta.hpp"

using RenderContext = Application;

namespace ui
{
	void initialize();
}

template<>
struct Serializer<Color>
{
	static Result load( Color& color, const Json& json);
	static Result save( const Color& color, Json& json);	
};