workspace "SolarSimulator"
    architecture "x86_64"
    startproject "SolarSim"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "%{wks.location}/Pandora/vendor/spdlog/include/"
IncludeDir["glm"] = "%{wks.location}/Pandora/vendor/glm"
IncludeDir["tinyobjloader"] = "%{wks.location}/Pandora/vendor/tinyobjloader/"
IncludeDir["stb_image"] = "%{wks.location}/Pandora/vendor/stb_image/"
IncludeDir["imgui"] = "%{wks.location}/Pandora/vendor/imgui/"

include "Pandora/vendor/imgui"

include "Pandora"
include "SolarSim"