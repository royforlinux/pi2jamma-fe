#pragma once

#include <stdio.h>


#define PRINT(message) \
	fprintf(stderr, "%s", message)

#define PRINTFMT(fmt, ...) \
	fprintf(stderr, fmt, __VA_ARGS__)

#define STOP() { PRINT("STOP()!\n"); __asm__("int3"); }

#define ASSERTFMT(x, message, ...) \
	{ \
		if(!(x)) { \
			PRINTFMT("Assertion Failed!: %s\n", #x); \
			PRINTFMT(message, __VA_ARGS__); \
			PRINT("\n"); \
			STOP(); \
		} \
	}

#define ASSERTMSG(x, message) \
	ASSERTFMT((x), "%s", message)	

#define ASSERT(x) \
	ASSERTMSG(x, "")
