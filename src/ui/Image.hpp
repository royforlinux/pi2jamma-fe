#pragma once

#include "ui/Element.hpp"

class Image final : public Element
{
	public:

		Image(
			Element* pParent,
			const char* filePath);

	protected:

		virtual void render(RenderContext& renderContext) override;

	private:

		Surface mSurface;
};