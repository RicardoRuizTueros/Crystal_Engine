workspace "Crystal_Engine"
	architecture "x86_64"
	startproject "Crystal_Editor"
	
	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Crystal_Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Crystal_Engine/vendor/Glad/include"
IncludeDir["imgui"] = "Crystal_Engine/vendor/imgui"
IncludeDir["glm"] = "Crystal_Engine/vendor/glm"
IncludeDir["stb_image"] = "Crystal_Engine/vendor/stb_image"
IncludeDir["entt"] = "Crystal_Engine/vendor/entt"

group "Dependencies"
	include "Crystal_Engine/vendor/GLFW"
	include "Crystal_Engine/vendor/Glad"
	include "Crystal_Engine/vendor/imgui"
group ""

project "Crystal_Engine"
	location "Crystal_Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "crystalpch.h"
	pchsource "Crystal_Engine/src/crystalpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/stb_image.h",
		"%{prj.name}/vendor/stb_image/stb_image.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
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
		"Crystal_Engine/vendor/spdlog/include",
		"Crystal_Engine/src",
		"Crystal_Engine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Crystal_Engine"
	}

	filter "system:windows"
		systemversion "latest"

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
			
project "Crystal_Editor"
	location "Crystal_Editor"
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
		"Crystal_Engine/vendor/spdlog/include",
		"Crystal_Engine/src",
		"Crystal_Engine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Crystal_Engine"
	}

	filter "system:windows"
		systemversion "latest"

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