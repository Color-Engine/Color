OutputDir = {}
OutputDir["__Completer__"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir.__Completer__}"
OutputDir["Objects"] = "%{wks.location}/Binaries-Int/%{OutputDir.__Completer__}"

ProjectDir = {}
ProjectDir["Color"] = "%{wks.location}/Color"
ProjectDir["Sandbox"] = "%{wks.location}/Sandbox"

IncludeDir = {}
IncludeDir["Color"] = "%{ProjectDir.Color}/Source"
IncludeDir["Sandbox"] = "%{ProjectDir.Sandbox}/Source"
