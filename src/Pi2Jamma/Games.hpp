#pragma once

#if 0

enum class Emulator {
	LrMame2000,
	LrMame2003,
	LrFinalBurnAlpha
};

class Emulator;

class Game
{
public:
	PROPERTY(std::string, Name);
	PROPERTY(std::string, RomName);

	Emulator* mpEmulator;
};

class Emulator
{
public:
	PROPERTY(std::string, Name);
};

class Games
{
	RbTree<
		Emulator,
		CStr,
		KeyFinder
};

#endif

