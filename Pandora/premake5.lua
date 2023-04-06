project "Pandora"
    kind "StaticLib"
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

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
        "src",
        "vendor/spdlog/include/",
        "vendor/glm/"
    }

    links
    {
        "glfw",
        "GLEW",
        "GL"
    }

    filter "configurations:Debug"
        defines "PD_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
		defines "PD_RELEASE"
		runtime "Release"
		optimize "on"