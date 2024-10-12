project "ImGui"
	kind "StaticLib"
	language "C++"
    staticruntime "off"

	targetdir "%{wks.location}/bin/%{cfg.name}"
	objdir    "%{wks.location}/obj/%{cfg.name}"

	files
	{
		"ImGui/**.cpp",
		"ImGui/**.h"
	}

	includedirs {
		"ImGui",
		"GLFW/include"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
