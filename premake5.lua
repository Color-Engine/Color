workspace "Color"
    architecture "x64"
    configurations
    {
        "Development",
        "Preview",
        "Shipping"
    }
    startproject "Sandbox"

include "Globals.lua"

group "Engine"
    include "Color"
group ""

group "Templates"
    include "Sandbox"
group ""
