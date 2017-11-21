#pragma once

#include <stdio.h>

#define PRINT(message) \
	fprintf(stderr, "%s", message)

#define PRINTFMT(fmt, ...) \
	fprintf(stderr, fmt, __VA_ARGS__)

#define STOP() { PRINT("STOP()!\n"); __asm__("int3"); }

#define ASSERTMSG(x, message) \
	{ \
		if(!x) { \
			PRINTFMT("Assertion Failed!: %s\n", #x); \
			PRINT(message); \
			PRINT("\n"); \
			STOP(); \
		} \
	}

#define ASSERT(x) \
	ASSERT_MSG(x, "")

inline void Log(const char* msg)
{
	printf(msg);
	printf("\n");
}





