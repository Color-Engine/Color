OutputDir = {}
OutputDir["__Completer__"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir.__Completer__}"
OutputDir["Objects"] = "%{wks.location}/Binaries-Int/%{OutputDir.__Completer__}"

ProjectDir = {}
ProjectDir["Color"] = "%{wks.location}/Color"
ProjectDir["Sandbox"] = "%{wks.location}/Sandbox"
ProjectDir["fmt"] = "%{ProjectDir.Color}/ThirdParty/fmt"

IncludeDir = {}
IncludeDir["Color"] = "%{ProjectDir.Color}/Source"
IncludeDir["Sandbox"] = "%{ProjectDir.Sandbox}/Source"
IncludeDir["spdlog"] = "%{ProjectDir.Color}/ThirdParty/spdlog/include"
IncludeDir["glm"] = "%{ProjectDir.Color}/ThirdParty/glm"
IncludeDir["fmt"] = "%{ProjectDir.fmt}/include"
