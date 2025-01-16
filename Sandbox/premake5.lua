project "Sandbox"
    language "C++"
    cppdialect "C++17"
    
    targetdir "%{OutputDir.Binaries}/%{prj.name}"
    objdir    "%{OutputDir.Objects}/%{prj.name}"

    files
    {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs
    {
        "%{IncludeDir.Color}",
        "Source"
    }

    links
    {
        "Color"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "CL_PLATFORM_WINDOWS",
            "CL_STABLE_PLATFORM"
        }

    filter "system:linux"
        defines
        {
            "CL_PLATFORM_LINUX",
            "CL_EXPERIMENTAL_PLATFORM"
        }
    
    filter "architecture:x64"
        defines
        {
            "CL_ARCH_X64"
        }

    filter "configurations:Development"
        runtime "Debug"
        symbols "On"
        kind "ConsoleApp"
        defines
        {
            "CL_DEVELOPMENT",
            "CL_TEST_BUILD"
        }
    
    filter "configurations:Preview"
        runtime "Release"
        optimize "Speed"
        kind "ConsoleApp"
        defines
        {
            "CL_PREVIEW",
            "CL_TEST_BUILD"
        }
    
    filter "configurations:Shipping"
        runtime "Release"
        optimize "Speed"
        kind "WindowedApp"
        defines
        {
            "CL_SHIPPING",
            "CL_DIST_BUILD"
        }
