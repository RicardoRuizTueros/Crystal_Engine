include "./vendor/premake/custom/solution_items.lua"
include "Dependencies.lua"

workspace "Crystal_Engine"
	architecture "x86_64"
	startproject "Crystal_Editor"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
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
