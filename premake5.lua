-- Workspace Setup
workspace "facerecognition"
    startproject "facerecognition"
	architecture "x86_64"
    language "c++"
    cppdialect "c++17"
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
    sysincludedirs {
        "/usr/local/include/opencv4"
    }
    files {
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.cpp",
    }
    libdirs {
        "/usr/local/lib"
    }
    links {
        "opencv_core.4.5.2",
        "opencv_face.4.5.2",
        "opencv_video.4.5.2",
        "opencv_videoio.4.5.2",
        "opencv_imgproc.4.5.2",
        "opencv_objdetect.4.5.2",
        "opencv_highgui.4.5.2",
        "opencv_imgcodecs.4.5.2",
    }
    
    if os.ishost("macosx") then
        postbuildcommands {
            "cp %{prj.location}/data/Info.plist %{wks.location}/bin/Info.plist"
        }
      links {'Cocoa.framework'}
      files "%{prj.location}/src/osx/**"
    end
    
