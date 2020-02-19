#pragma once

#include "crystal/core/Core.h"

#ifdef CRYSTAL_PLATFORM_WINDOWS

extern Crystal::Application* Crystal::CreateApplication();

int main(int argc, char** argv)
{
	Crystal::Log::Init();

	CRYSTAL_PROFILE_BEGIN_SESSION("Startup", "CrystalProfile-Startup.json");
	auto sandbox = Crystal::CreateApplication();
	CRYSTAL_PROFILE_END_SESSION();

	CRYSTAL_PROFILE_BEGIN_SESSION("Run", "CrystalProfile-Run.json");
	sandbox->Run();
	CRYSTAL_PROFILE_END_SESSION();

	CRYSTAL_PROFILE_BEGIN_SESSION("Startup", "CrystalProfile-Shutdown.json");
	delete sandbox;
	CRYSTAL_PROFILE_END_SESSION();
}

#endif
