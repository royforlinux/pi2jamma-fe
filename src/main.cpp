#include "ui/application.hpp"

int main(int argv, const char* argc[])
{
	Application application;

	auto result = application.initialize();

	result.catastrophic();

	result = application.run();

	if(result.succeeded())
	{
		return 0;
	}

	return -1;
}