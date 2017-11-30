#pragma once

#include "ui/ui.hpp"
#include "core/Property.hpp"

class KeyConfiguration
{
	public:

		static void initialize();

		KeyConfiguration();
		
		PROPERTY(Key, Up)
		PROPERTY(Key, Down);
		PROPERTY(Key, Left);
		PROPERTY(Key, Right);
		PROPERTY(Key, Select);
		PROPERTY(Key, Back);
};
