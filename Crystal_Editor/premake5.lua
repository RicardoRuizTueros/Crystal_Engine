project "Crystal_Editor"
	location "Crystal_Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Crystal_Engine/vendor/spdlog/include",
		"%{wks.location}/Crystal_Engine/src",
		"%{wks.location}/Crystal_Engine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
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