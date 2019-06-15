workspace "Crystal_Engine_v2"
	architecture "x64"

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


include "Crystal_Engine_v2/vendor/GLFW"
include "Crystal_Engine_v2/vendor/Glad"


project "Crystal_Engine_v2"
	location "Crystal_Engine_v2"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "crystalpch.h"
	pchsource "Crystal_Engine_v2/src/crystalpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"CRYSTAL_PLATFORM_WINDOWS",
			"CRYSTAL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "CRYSTAL_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "CRYSTAL_RELEASE"
			buildoptions "/MD"
			symbols "On"

		filter "configurations:Distribution"
			defines "CRYSTAL_DISTRIBUTION"
			buildoptions "/MD"
			symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Crystal_Engine_v2/src"
	}

	links
	{
		"Crystal_Engine_v2"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"CRYSTAL_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "CRYSTAL_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "CRYSTAL_RELEASE"
			buildoptions "/MD"
			symbols "On"

		filter "configurations:Distribution"
			defines "CRYSTAL_DISTRIBUTION"
			buildoptions "/MD"
			symbols "On"