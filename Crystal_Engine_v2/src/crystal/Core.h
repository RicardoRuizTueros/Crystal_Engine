#pragma once

#ifdef CRYSTAL_PLATFORM_WINDOWS
	#ifdef CRYSTAL_BUILD_DLL
		#define CRYSTAL_API __declspec(dllexport)
	#else
		#define CRYSTAL_API __declspec(dllimport)
	#endif
#else
	#error Crystal only supports Window!
#endif

