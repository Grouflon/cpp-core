project "core"

	kind "StaticLib"
	language "C++"
	architecture "x86"
	flags { "Symbols", "MultiProcessorCompile" }
	
	targetdir "libs/%{cfg.platform}/%{cfg.buildcfg}/"
	objdir "obj/%{cfg.platform}/%{cfg.buildcfg}/"
	
	pchheader "stdafx.h"
	pchsource "src/stdafx.cpp"

	files {
		"src/**.cpp",
		"src/**.c",
		"src/stdafx.h",
		"include/**.inl",
		"include/**.h",
		"extern/imgui/**.cpp",
		"extern/imgui/**.c",
		"extern/imgui/**.h",
		"extern/gl3w/**.c",
		"extern/gl3w/**.h",
		"extern/glm/**.hpp",
		"extern/json/**.c",
		"extern/json/**.h",
		"extern/openAL/**.h",
		"extern/audio/**.c",
		"extern/audio/**.h",
		"extern/SDL2-2.0.4/**.h",
	}
			
	removefiles {
		"extern/imgui/imgui_impl_sfml**",
		"extern/imgui/imgui_impl_glfw_gl3**",
	}
			
	includedirs {
		"src/",
		"include/",
		"extern/gl3w/",
		"extern/glm/",
		"extern/imgui/",
		"extern/json/",
		"extern/openAL/include",
		"extern/audio/",
		"extern/SDL2-2.0.4/include",
	}
			
	defines {
		"_CRT_SECURE_NO_WARNINGS", "IMGUI_INCLUDE_IMGUI_USER_H=1"
	}
	
	filter "files:extern/**"
		flags "noPCH"
	
	filter "configurations:debug"
			optimize "Off"
			defines "_DEBUG"
			
	filter "configurations:release"
		optimize "Full"

	filter {}