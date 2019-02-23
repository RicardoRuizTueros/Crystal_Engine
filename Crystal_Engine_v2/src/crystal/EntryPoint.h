#pragma once

#ifdef CRYSTAL_PLATFORM_WINDOWS

extern crystal::Application* crystal::CreateApplication();

int main(int argc, char** argv)
{
	crystal::Log::Init();
	crystal::Log::GetCoreLogger()->warn("Initialized log!");
	crystal::Log::GetClientLogger()->info("Hello!");


	auto sandbox = crystal::CreateApplication();
	sandbox->Run();
	delete sandbox;
}

#endif
