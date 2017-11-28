#include "ui/device/ui.hpp"

#include "core/meta/Meta.hpp"

namespace ui
{

void initialize() {
	META_ENUM(Key);
	META_ENUM_VALUE(Key, DownArrow);
	META_ENUM_VALUE(Key, UpArrow);
	META_ENUM_VALUE(Key, Escape);
	META_ENUM_VALUE(Key, Space);

	META_CLASS(Rect);

	META_CLASS_PROPERTY(Rect, X);
	META_CLASS_PROPERTY(Rect, Y);
	META_CLASS_PROPERTY(Rect, Width);
	META_CLASS_PROPERTY(Rect, Height);
}

} // namespace ui

template<>
Result Serializer<Color>::load( Color& color, const Json& json)
{
	if( json.IsObject()) {
		return Meta::get().findType<Color>()->load(&color, json);
	}

	if ( !json.IsString())
	{
		return Result::makeFailureWithStringLiteral( "Color value json not valid.");

	}

	std::string& str = json.GetString();
	if( str[0] != '#') {
		return Result::makeFailureWithStringLiteral( "Color string doesn't start witn a '#'");
	}

	int chars = 0;
	uint32_t iColor = static_cast<uint32_t>(std::stoi(& str[1], & chars, 16));

	if(chars == 6)
	{
		uint8_t r = (iColor & 0x00FF0000) >> 16;
		uint8_t g = (iColor & 0x0000FF00) >> 8;
		uint8_t b = (iColor & 0x000000FF);

		color = Color(r, g, b);

		return Result::makeSuccess();
	}

	return Result::makeFailureWithStringLiteral("Bad color string value" );

}

template<>
Result Serializer<Color>::save( const Color& color, Json& json)
{
	return Meta::get().findType<Color>()->save(&color, json);
}
