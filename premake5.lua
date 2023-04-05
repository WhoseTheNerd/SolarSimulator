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

include "Pandora"
include "SolarSim"