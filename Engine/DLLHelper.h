#pragma once

//used to make it easier to mark what methods needs to be exported for use outside the dll
#if COMPILING_DLL
#define DLLEXTERN __declspec(dllexport)
#else
#define DLLEXTERN __declspec(dllimport)
#endif