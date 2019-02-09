#pragma once

#if COMPILING_DLL
#define DLLEXTERN __declspec(dllexport)
#else
#define DLLEXTERN __declspec(dllimport)
#endif