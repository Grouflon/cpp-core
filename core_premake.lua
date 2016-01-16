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
	"extern/json/**.c",
	"extern/json/**.h",
	"extern/openAL/**.h",
}
		
removefiles {
	"extern/imgui/imgui_impl_sfml**",
}
		
includedirs {
	"src/",
	"extern/glfw/include",
	"extern/gl3w/",
	"extern/glm/",
	"extern/imgui/",
	"extern/json/",
	"extern/openAL/include",
}
		
libdirs {
	"extern/glfw/libs/%{cfg.buildcfg}/",
	"extern/openAL/libs/%{cfg.platform}/",
}
		
links {
	"glfw3",
	"opengl32",
	"OpenAL32",
}
		
defines {
	"_CRT_SECURE_NO_WARNINGS", "IMGUI_INCLUDE_IMGUI_USER_H=1"
}
