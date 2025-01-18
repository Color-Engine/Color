project "Color"
    language "C++"
    cppdialect "C++17"
    kind "StaticLib"

    targetdir "%{OutputDir.Binaries}/%{prj.name}"
    objdir    "%{OutputDir.Objects}/%{prj.name}"

    pchheader "EnginePCH.h"
    pchsource "Source/EnginePCH.cpp"

    files
    {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs
    {
        "Source",
		
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.fmt}"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "CL_PLATFORM_WINDOWS",
            "CL_STABLE_PLATFORM",
			
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
			"_CRT_SECURE_NO_WARNINGS"
        }
        excludes
        {
            "Source/Platform/Linux/**.cpp"
        }

    filter "system:linux"
        defines
        {
            "CL_PLATFORM_LINUX",
            "CL_EXPERIMENTAL_PLATFORM"
        }
        excludes
        {
            "Source/Platform/Windows/**.cpp"
        }
    
    filter "architecture:x64"
        defines
        {
            "CL_ARCH_X64"
        }

    filter "configurations:Development"
        runtime "Debug"
        symbols "On"
        defines
        {
            "CL_DEVELOPMENT",
            "CL_TEST_BUILD"
        }
    
    filter "configurations:Preview"
        runtime "Release"
        optimize "Speed"
        defines
        {
            "CL_PREVIEW",
            "CL_TEST_BUILD"
        }
    
    filter "configurations:Shipping"
        runtime "Release"
        optimize "Speed"
        defines
        {
            "CL_SHIPPING",
            "CL_DIST_BUILD"
        }
