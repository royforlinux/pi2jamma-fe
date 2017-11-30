#pragma once

#include "ui/device/UiDevice.hpp"

#include "core/meta/Meta.hpp"

namespace ui
{
	void initialize();
}

template<>
struct Serializer<Color>
{
	static Result load( Color& color, ObjectReadStream& readStream);
	static Result save( const Color& color, ObjectWriteStream& writeStream);	
};