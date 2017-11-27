#pragma once

#include "ui/device/sdl2/sdl2types.hpp"
#include "ui/device/sdl2/Color.hpp"
#include "ui/device/sdl2/Rect.hpp"
#include "ui/device/sdl2/KeyDownEvent.hpp"
#include "ui/device/sdl2/Surface.hpp"
#include "ui/device/sdl2/Font.hpp"

#include "core/Result.hpp"

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

		Result loadSurface(ref<Surface>& surface, const char* filename);
		
		Result loadFont(
			ref<Font>& refFont,
			UnitType sizePx,
			const char* filename);
		
		Result renderText(
			ref<Surface>& refSurface,
			const ref<Font>& font,
			const Color& color,
			const char* text);

		void draw(const ref<Surface>& refSurface, const Rect& source, const Rect& target);
		void draw(const ref<Surface>& refSurface, const Point& targetPoint);
		void drawRect(const Rect& rect, const Color& color);
		
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
