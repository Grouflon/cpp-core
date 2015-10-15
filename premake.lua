solution "playground"
	platforms { "Win32" }
	configurations { "Debug", "Release" }
	
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