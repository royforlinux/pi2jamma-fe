#pragma once

#include "ui/sdl2/sdl2types.hpp"
#include "ui/sdl2/Rect.hpp"
#include "ui/surface.hpp"

#include "result.hpp"

class Application
{
	public:

		Application();
		~Application();

		Result run();
		inline void quit();

		virtual Result initialize() = 0;
		virtual void render() = 0;

		Result loadSurface(Surface& surface, const char* filename);
		void draw(Surface& surface, const Rect& source, const Rect& target);
		void draw(Surface& surface, const Point& targetPoint);

	private:

		Result renderLoop();		

		bool mQuit;

		std::unique_ptr<SDL_Renderer> muptSdlRenderer;
		std::unique_ptr<SDL_Window> muptSdlWindow;
	
};

inline void Application::quit()
{
	mQuit = true;
}
