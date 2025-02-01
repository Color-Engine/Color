OutputDir = {}
OutputDir["__Completer__"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir.__Completer__}"
OutputDir["Objects"] = "%{wks.location}/Binaries-Int/%{OutputDir.__Completer__}"

ProjectDir = {}
ProjectDir["Color"] = "%{wks.location}/Color"
ProjectDir["Sandbox"] = "%{wks.location}/Sandbox"
ProjectDir["GLFW"] = "%{ProjectDir.Color}/ThirdParty/GLFW"
ProjectDir["Glad"] = "%{ProjectDir.Color}/ThirdParty/Glad"
ProjectDir["fmt"] = "%{ProjectDir.Color}/ThirdParty/fmt"

IncludeDir = {}
IncludeDir["Color"] = "%{ProjectDir.Color}/Source"
IncludeDir["Sandbox"] = "%{ProjectDir.Sandbox}/Source"
IncludeDir["GLFW"] = "%{ProjectDir.GLFW}/include"
IncludeDir["Glad"] = "%{ProjectDir.Glad}/include"
IncludeDir["fmt"] = "%{ProjectDir.fmt}/include"
IncludeDir["spdlog"] = "%{ProjectDir.Color}/ThirdParty/spdlog/include"
IncludeDir["glm"] = "%{ProjectDir.Color}/ThirdParty/glm"
