#pragma once

#include "ui/surface.hpp"
#include "ui/window.hpp"

class Application
{
	public:

		Application();
		~Application();

		Result initialize();
		Result run();

		Surface& getPrimarySurface();

	private:

		Surface mPrimarySurface;
		Window mWindow;
};

inline Surface& Application::getPrimarySurface()
{
	return mPrimarySurface;
}