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
			"src/**.inl",
			"src/**.c",
			"src/**.h",
			"extern/imgui/**.cpp",
			"extern/imgui/**.c",
			"extern/imgui/**.h",
			"extern/glfw/**.h",
			"extern/gl3w/**.c",
			"extern/gl3w/**.h",
			"extern/glm/**.hpp",
			"extern/openAL/**.h",
		}
		
		removefiles {
			"extern/imgui/imgui_impl_sfml**",
		}
		
		includedirs {
			"src/",
			"extern/SFML/include",
			"extern/glfw/include",
			"extern/gl3w/",
			"extern/glm/",
			"extern/imgui/",
			"extern/openAL/include",
		}
		
		libdirs {
			"extern/glfw/libs/%{cfg.buildcfg}/",
			"extern/openAL/libs/%{cfg.platform}/",
		}
		
		links {
			"glfw3",
			"opengl32",
			--"winmm",
			--"gdi32",
			"OpenAL32"
		}
		
		defines {
			"_CRT_SECURE_NO_WARNINGS",
		}
		
		filter "files:extern/**"
		
			flags "noPCH"
		
		filter "configurations:debug"
			
			optimize "Off"
			defines "_DEBUG"
			
		filter "configurations:release"
		
			optimize "Full"
		