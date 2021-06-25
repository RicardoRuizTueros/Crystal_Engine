#include "crystalpch.h"
#include "Crystal/utils/PlatformUtils.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "crystal/core/Application.h"

namespace Crystal
{
	string FileDialogs::OpenFile(const char* filter)
	{
		OPENFILENAMEA openFileName;
		CHAR fileSize[255] = { 0 };
		CHAR currentDirectory[256] = { 0 };
		ZeroMemory(&openFileName, sizeof(openFileName));
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		openFileName.lpstrFile = fileSize;
		openFileName.nMaxFile = sizeof(fileSize);

		if (GetCurrentDirectoryA(256, currentDirectory))
			openFileName.lpstrInitialDir = currentDirectory;

		openFileName.lpstrFilter = filter;
		openFileName.nFilterIndex = 1;
		openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&openFileName) == TRUE)
			return openFileName.lpstrFile;
		 
		return string();
	}

	string FileDialogs::SaveFile(const char* filter)
	{
		OPENFILENAMEA openFileName;
		CHAR fileSize[255] = { 0 };
		CHAR currentDirectory[256] = { 0 };

		ZeroMemory(&openFileName, sizeof(openFileName));
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		openFileName.lpstrFile = fileSize;
		openFileName.nMaxFile = sizeof(fileSize);

		if (GetCurrentDirectoryA(256, currentDirectory))
			openFileName.lpstrInitialDir = currentDirectory;

		openFileName.lpstrFilter = filter;
		openFileName.nFilterIndex = 1;
		openFileName.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
		openFileName.lpstrDefExt = strchr(filter, '\0') + 1;

		if (GetSaveFileNameA(&openFileName) == TRUE)
			return openFileName.lpstrFile;

		return string();
	}
}
