-- Workspace Setup
workspace "facerecognition"
    startproject "facerecognition"
	architecture "x86_64"
    language "c++"
    cppdialect "c++11"
    configurations {
        "Debug",
        "Release"
    }
-- Configuration Settings
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    filter ""

-- Project Setup
project "facerecognition"
    objdir "bin-obj"
    targetdir "bin"
    location "facerecognition"
    kind "ConsoleApp"
    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp",
    }
    
