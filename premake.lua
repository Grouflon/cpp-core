solution "playground"
	platforms { "Win32" }
	configurations { "debug", "release" }
	
	location("project/" .. _ACTION)

	startproject "playground"
	
	project "playground"
		kind "ConsoleApp"
		language "C++"
		flags { "Symbols", "MultiProcessorCompile" }
		rtti "On"
		editandcontinue "On"
		
		targetdir "bin/%{cfg.platform}/%{cfg.buildcfg}/"
		objdir "obj/%{cfg.platform}/%{cfg.buildcfg}/"
		
		debugdir "."
		
		pchheader "stdafx.h"
		pchsource "src/stdafx.cpp"
		
		files {
			"src/**.cpp",
			"src/**.c",
			"src/**.h",
			"extern/imgui/**.cpp",
			"extern/imgui/**.c",
			"extern/imgui/**.h",
		}
		
		includedirs {
			"src/",
			"extern/SFML/include",
			"extern/imgui/"
		}
		
		libdirs {
			"extern/SFML/lib/%{cfg.buildcfg}/",
		}
		
		links {
			"opengl32",
			"winmm",
			"gdi32",
			"sfml-system-s",
			"sfml-window-s",
		}
		
		defines "SFML_STATIC"
		
		filter "configurations:debug"
			
			defines "_DEBUG"
			
		filter "configurations:release"
		