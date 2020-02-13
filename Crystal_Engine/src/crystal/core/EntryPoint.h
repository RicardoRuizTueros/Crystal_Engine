#pragma once

#include "crystal/core/Core.h"

#ifdef CRYSTAL_PLATFORM_WINDOWS

extern Crystal::Application* Crystal::CreateApplication();

int main(int argc, char** argv)
{
	Crystal::Log::Init();

	CRYSTAL_CORE_WARN("Initialized log!");
	int a = 5;
	CRYSTAL_INFO("Hello var={0}", a);

	auto sandbox = Crystal::CreateApplication();
	sandbox->Run();
	delete sandbox;
}

#endif
