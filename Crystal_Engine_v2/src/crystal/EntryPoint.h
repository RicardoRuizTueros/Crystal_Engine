#pragma once

#ifdef CRYSTAL_PLATFORM_WINDOWS

extern Crystal::Application* Crystal::CreateApplication();

int main(int argc, char** argv)
{
	Crystal::Log::Init();
	Crystal::Log::GetCoreLogger()->warn("Initialized log!");
	Crystal::Log::GetClientLogger()->info("Hello!");


	auto sandbox = Crystal::CreateApplication();
	sandbox->Run();
	delete sandbox;
}

#endif
