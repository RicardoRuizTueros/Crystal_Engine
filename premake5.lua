include "./vendor/premake/custom/solution_items.lua"

workspace "Crystal_Engine"
	architecture "x86_64"
	startproject "Crystal_Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Crystal_Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Crystal_Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Crystal_Engine/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Crystal_Engine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Crystal_Engine/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Crystal_Engine/vendor/entt"
IncludeDir["yaml_cpp"] = "%{wks.location}/Crystal_Engine/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Crystal_Engine/vendor/ImGuizmo"

group "Dependencies"
	include "vendor/premake"
	include "Crystal_Engine/vendor/GLFW"
	include "Crystal_Engine/vendor/Glad"
	include "Crystal_Engine/vendor/imgui"
	include "Crystal_Engine/vendor/yaml-cpp"
group ""

include "Crystal_Engine"
include "Crystal_Editor"
include "Sandbox"
