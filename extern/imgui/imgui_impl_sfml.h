#pragma once

// ImGui SFML binding with OpenGL
// You can copy and use unmodified imgui_impl_* files in your project. 
// If you use this binding you'll need to call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(), ImGui::Render() and ImGui_ImplXXXX_Shutdown().
// See main.cpp for an example of using this.
// https://github.com/ocornut/imgui

namespace sf {
	class Window;
	class Event;
}

IMGUI_API bool        ImGui_ImplSfml_Init(sf::Window* window);
IMGUI_API void        ImGui_ImplSfml_Shutdown();
IMGUI_API void        ImGui_ImplSfml_NewFrame(sf::Window* window);
IMGUI_API bool        ImGui_ImplSfml_ProcessEvent(sf::Event* event);

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void        ImGui_ImplSfml_InvalidateDeviceObjects();
IMGUI_API bool        ImGui_ImplSfml_CreateDeviceObjects();