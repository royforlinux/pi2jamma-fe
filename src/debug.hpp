#pragma once

#include <stdio.h>

#define DEBUG_CONTAINER

#define PRINT(message) \
	fprintf(stderr, "%s", message)

#define PRINTFMT(fmt, ...) \
	fprintf(stderr, fmt, __VA_ARGS__)

#define STOP() { PRINT("STOP()!\n"); __asm__("int3"); }

#define ASSERTMSG(x, message) \
	{ \
		if(!(x)) { \
			PRINTFMT("Assertion Failed!: %s\n", #x); \
			PRINT(message); \
			PRINT("\n"); \
			STOP(); \
		} \
	}

#define ASSERT(x) \
	ASSERTMSG(x, "")

inline void Log(const char* msg)
{
	printf(msg);
	printf("\n");
}

#define LogFmt(fmt, ...) \
{ \
	printf(fmt, __VA_ARGS__); \
}
