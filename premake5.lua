workspace "LearnOpenGL"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release"
    }


outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "LearnOpenGL"
    location "LearnOpenGL"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" ..outputDir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputDir.. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "%{prj.name}/src/pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/Externals/includes"
    }

    libdirs
    {
        "%{prj.name}/Externals/libs/VLD/",
        "%{prj.name}/Externals/libs/GLFW/",
        "%{prj.name}/Externals/libs/GLEW/",
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        links
        {
            "vld.lib",
            "opengl32.lib",
            "glew32.lib",
            "glfw3.lib",
        }

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"


