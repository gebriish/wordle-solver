workspace "WordleSolver"
    architecture "x86_64"
    configurations {
        "Debug", "Release"
    }

project "Solver"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

	targetdir "%{wks.location}/bin/%{cfg.name}"
	objdir    "%{wks.location}/obj/"

    files {
        "src/**.cpp",
        "src/**.h"
    }

    includedirs {
        "src",
        "vendor/GLFW/include",
        "vendor/GLAD/include",
		"vendor/ImGui",
    }

    links {
        "GLAD",
        "GLFW",
        "ImGui"
    }

    filter "configurations:Debug"
        defines {
            "DEBUG"
        }
        symbols "on"

    filter "configurations:Release"
        defines {
            "NDEBUG"
        }
        optimize "speed"

group "dependencies"
    include "vendor/imgui.lua"
    include "vendor/glfw.lua"
    include "vendor/glad.lua"
group ""
