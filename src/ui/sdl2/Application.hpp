#pragma once

#include "ui/sdl2/sdl2types.hpp"
#include "ui/sdl2/Color.hpp"
#include "ui/sdl2/Rect.hpp"
#include "ui/sdl2/KeyDownEvent.hpp"
#include "ui/sdl2/Surface.hpp"
#include "ui/sdl2/Font.hpp"

#include "result.hpp"

class Application
{
	public:

		Application();
		~Application();

		static Application* get();

		Result run();
		void quit();

		virtual Result initialize() = 0;
		virtual void render() = 0;
		virtual void keyDownEvent(const KeyDownEvent& keyDownEvent) = 0;

		Result loadSurface(Surface& surface, const char* filename);
		Result loadFont(Font& font, const char* filename);
		
		Result renderText(
			Surface& surface,
			const Font& font,
			const Color& color,
			const char* text);

		void draw(Surface& surface, const Rect& source, const Rect& target);
		void draw(Surface& surface, const Point& targetPoint);

	private:

		Result renderLoop();
		void dispatchEvent(const SDL_Event& sdlEvent);		

		bool mQuit;

		std::unique_ptr<SDL_Renderer> muptSdlRenderer;
		std::unique_ptr<SDL_Window> muptSdlWindow;

		static Application* spSingleton;
	
};

inline Application* Application::get()
{
	ASSERT(nullptr != spSingleton);
	return spSingleton;
}

inline void Application::quit()
{
	mQuit = true;
}
