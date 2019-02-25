workspace "Crystal_Engine_v2"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Crystal_Engine_v2"
	location "Crystal_Engine_v2"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"CRYSTAL_PLATFORM_WINDOWS",
			"CRYSTAL_BUILD_DLL"
		}

		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} .. /bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "CRYSTAL_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "CRYSTAL_RELEASE"
			symbols "On"

		filter "configurations:Distribution"
			defines "CRYSTAL_DISTRIBUTION"
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
		"%{prj.name}/vendor/spdlog/include",
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
			symbols "On"

		filter "configurations:Release"
			defines "CRYSTAL_RELEASE"
			symbols "On"

		filter "configurations:Distribution"
			defines "CRYSTAL_DISTRIBUTION"
			symbols "On"