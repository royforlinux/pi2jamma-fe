#pragma once

#include "ui/ui.hpp"
#include "core/Property.hpp"

class Configuration
{
public:
	static void initialize();

	Configuration();

	PROPERTY(Key, UpKey)
	PROPERTY(Key, DownKey);
	PROPERTY(Key, LeftKey);
	PROPERTY(Key, RightKey);
	PROPERTY(Key, SelectKey);
	PROPERTY(Key, BackKey);

	PROPERTY(bool, SaveConfigOnExit);
};