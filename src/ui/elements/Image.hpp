#pragma once

#include "ui/elements/Element.hpp"

class Image final : public Element
{
	public:

		Image(
			Element* pParent,
			const char* filePath);

	protected:

		virtual void render(RenderContext& renderContext) override;
		virtual void resize(const Size& oldSize, const Size& newSize) override;

	private:

		ref<Surface> mrefSurface;
};