#pragma once

#include "Pi2Jamma/Configuration/KeyConfiguration.hpp"

class Configuration
{
public:
	static void initialize();

	Configuration();

	PROPERTY(bool, SaveConfigOnExit);
	PROPERTY(KeyConfiguration, Keys);
};