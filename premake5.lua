project "cpp-core"
	kind "StaticLib"
	language "C++"

	files {
		"src/core/Types.h",
		"src/core/Assert.h",
		"src/core/Clock.h",
		"src/core/Clock.cpp",
		"src/core/Time.h",
		"src/core/Time.cpp",
		"src/core/Log.h",
		"src/core/Log.cpp",
		"src/core/File.h",
		"src/core/File.cpp",
		"src/core/FileHandle.h",
		"src/core/FileHandle.cpp",
		"src/core/Resource.h",
		"src/core/Resource.cpp",

		"extern/glm/**.hpp",
		"extern/glm/**.cpp",

		"extern/imgui/imconfig.h",
		"extern/imgui/imgui.cpp",
		"extern/imgui/imgui.h",
		"extern/imgui/imgui_demo.cpp",
		"extern/imgui/imgui_draw.cpp",
		"extern/imgui/imgui_internal.h",
		"extern/imgui/imgui_internal.h",
		"extern/imgui/stb_rect_pack.h",
		"extern/imgui/stb_textedit.h",
		"extern/imgui/stb_truetype.h",
	}

	includedirs {
		"src/",
		"extern/",
		"extern/glm",
		"extern/imgui",
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
