#include "Pi2JammaApplication.hpp"

int main(int argv, const char* argc[])
{
	Pi2JammaApplication application;

	Result result = application.run();
	if(result.failed()) {
		Log(result.getMessage());
		return -1;
	}

	return 0;
}