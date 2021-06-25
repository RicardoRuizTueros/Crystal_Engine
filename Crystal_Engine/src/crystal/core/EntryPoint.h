#pragma once

#include "crystal/core/Base.h"
#include "crystal/core/Application.h"

#ifdef CRYSTAL_PLATFORM_WINDOWS

extern Crystal::Application* Crystal::CreateApplication(ApplicationCommandLineArguments arguments);

int main(int argc, char** argv)
{
	Crystal::Log::Init();

	CRYSTAL_PROFILE_BEGIN_SESSION("Startup", "CrystalProfile-Startup.json");
	auto application = Crystal::CreateApplication({ argc, argv });
	CRYSTAL_PROFILE_END_SESSION();

	CRYSTAL_PROFILE_BEGIN_SESSION("Run", "CrystalProfile-Run.json");
	application->Run();
	CRYSTAL_PROFILE_END_SESSION();

	CRYSTAL_PROFILE_BEGIN_SESSION("Shutdown", "CrystalProfile-Shutdown.json");
	delete application;
	CRYSTAL_PROFILE_END_SESSION();
}

#endif
