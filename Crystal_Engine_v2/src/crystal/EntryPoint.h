#pragma once

#ifdef CRYSTAL_PLATFORM_WINDOWS

extern crystal::Application* crystal::CreateApplication();

int main(int argc, char** argv)
{
	auto sandbox = crystal::CreateApplication();
	sandbox->Run();
	delete sandbox;
}

#endif
