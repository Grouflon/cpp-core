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
		
		files {
			"src/**.cpp",
			"src/**.c",
			"src/**.h",
		}
		
		includedirs {
			"src/",
		}
		
		includedirs {
			"extern/SFML/include"
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
			
			defines "DEBUG"
			
		filter "configurations:release"
		