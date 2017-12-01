#include "ui/Align.hpp"

struct Span {
	Span(UnitType start, UnitType length)
		: mStart(start)
		, mLength(length)
	{
	}

	PROPERTY(UnitType, Start);
	PROPERTY(UnitType, Length);
};

cropAxis(
	const Span& sourceSpan,
	const Span& targetSpan
	HorizontalAlignment alignment,
	CropMode cropMode)
{
	auto sourceLength = sourceSpan.getLength();
	auto targetLength = targetSpan.getLength();
	auto sourceStart = sourceSpan.getStart();
	auto targetStart = targetSpan.getStart();
	
	if(sourceSpan.getLength() > targetSpan.getLength()) {
		auto span = targetSp
	}

}
CropResult crop(
	Rect& targetOut,
	Rect& sourceOut,
	const Rect& target,
	const Rect& source,
	HorizontalAlignment horizontalAlignment,
	VerticalAlignment verticalAlignment,
	CropMode cropMode)
{
	auto sourceWidth = source.getWidth();
	auto targetWidth = target.getWidth();

	auto sourceX = source.getX();
	auto targetX = target.getX();

	UnitType sourceWidthOut;
	UintType targetWidthOut;
	UnitType targetXOut;
	UnitType targetYOut;

	// Center only, for now.

	if(targetWidth > sourceWidth) {
		auto width = targetWidth;
		auto halfWidth = width / 2;
		auto targetCenter = targetX + (targetWidth / 2);
		tagetXOut = targetCenter - halfWidth;
		targetWidthOut = width;

		auto sourceCenter = sourceX + (sourceWidth / 2);
		sourceXOut = sourceCenter - halfWidth;
		sourceWidthOut = width;
	}

	CropResult result;
	result.sourceRect = Rext(sourceXOut, )

	auto widthDif = sourceWidth - targetWidth;


	auto targetCenter = target.getCenter();
	auto sourceCenter = source.getCenter();


}


