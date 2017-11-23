#include "Pi2JammaApplication.hpp"

int main(int argv, const char* argc[])
{
	Pi2JammaApplication application;

	return application.run().succeeded() ? 0 : -1;
}