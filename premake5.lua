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

group "Engine/ThirdParty"
	include "Color/ThirdParty/GLFW"
	include "Color/ThirdParty/Glad"
	include "Color/ThirdParty/fmt"
group ""

group "Engine"
    include "Color"
group ""

group "Templates"
    include "Sandbox"
group ""
