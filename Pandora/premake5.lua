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
        "src/**.cpp",
        "vendor/stb_image/stb_image.h",
        "vendor/stb_image/stb_image.cpp",
        "vendor/tinyobjloader/tiny_obj_loader.h",
        "vendor/tinyobjloader/tiny_obj_loader.cc",
    }

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
        "src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.tinyobjloader}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.toml}"
    }

    links
    {
        "glfw",
        "GLEW",
        "GL",
        "ImGui"
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