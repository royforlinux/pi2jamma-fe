#include "ui/application.hpp"

class Pi2JammaApplication : public Application
{
	virtual Result initialize() override;

	virtual void render() override
	{
		draw(mBackground, Point(0,0));
	}

	Surface mBackground;
};

Result Pi2JammaApplication::initialize()
{
	return
		loadSurface(
			mBackground,
			"/home/x/arcade/pi2jamma-fe/themes/burgertime/background.png");

}
	

int main(int argv, const char* argc[])
{

	Pi2JammaApplication application;

	return application.run().succeeded() ? 0 : -1;
}