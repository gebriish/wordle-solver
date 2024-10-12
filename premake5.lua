workspace "WordleSolver"
    architecture "x86_64"
    configurations {
        "Debug", "Release"
    }

project "Solver"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir "%{wks.location}/bin/%{cfg.name}-%{prj.name}"
    objdir    "%{wks.location}/obj/%{cfg.name}-%{prj.name}"

    files {
        "src/**.cpp",
        "src/**.hpp"
    }

    includedirs {
        "src",
        "vendor/GLFW/include",
        "vendor/GLAD/include",
        "vendor/STB/include"
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
    include "vendor/glfw.lua"
    include "vendor/glad.lua"
group ""
