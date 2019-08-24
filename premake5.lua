workspace "Crystal_Engine_v2"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Crystal_Engine_v2/vendor/GLFW/include"
IncludeDir["Glad"] = "Crystal_Engine_v2/vendor/Glad/include"
IncludeDir["imgui"] = "Crystal_Engine_v2/vendor/imgui"
IncludeDir["glm"] = "Crystal_Engine_v2/vendor/glm"

group "Dependencies"
	include "Crystal_Engine_v2/vendor/GLFW"
	include "Crystal_Engine_v2/vendor/Glad"
	include "Crystal_Engine_v2/vendor/imgui"
group ""

project "Crystal_Engine_v2"
	location "Crystal_Engine_v2"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "crystalpch.h"
	pchsource "Crystal_Engine_v2/src/crystalpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"CRYSTAL_PLATFORM_WINDOWS",
			"CRYSTAL_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

		filter "configurations:Debug"
			defines "CRYSTAL_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "CRYSTAL_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Distribution"
			defines "CRYSTAL_DISTRIBUTION"
			runtime "Release"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Crystal_Engine_v2/vendor/spdlog/include",
		"Crystal_Engine_v2/src",
		"Crystal_Engine_v2/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Crystal_Engine_v2"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"CRYSTAL_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "CRYSTAL_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "CRYSTAL_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Distribution"
			defines "CRYSTAL_DISTRIBUTION"
			runtime "Release"
			optimize "On"