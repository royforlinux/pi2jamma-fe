#pragma once

#include "core/Property.hpp"
#include <string>
#include <vector>

class Game
{
public:
	static void initialize();

	PROPERTY(std::string, DisplayName);
};

class Games
{
public:
	static void initialize();

	PROPERTY(std::vector<Game>, GameList);
};