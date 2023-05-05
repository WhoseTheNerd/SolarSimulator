project "SolarSim"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.hpp",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "%{wks.location}/Pandora/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.tinyobjloader}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.toml}"
    }

    links
    {
        "Pandora",
        "ImGui",
        "glfw",
        "GLEW",
        "GL"
    }

    linkoptions { "-fuse-ld=mold" }
    buildoptions { "-pipe" }

    filter "configurations:Debug"
        defines "PD_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
		defines "PD_RELEASE"
		runtime "Release"
		optimize "on"