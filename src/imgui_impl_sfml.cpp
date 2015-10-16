#include <windows.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <imgui.h>
#include "imgui_impl_sfml.h"

// Data
static sf::Clock	g_Time;
static bool         g_MousePressed[3] = { false, false, false };
static float        g_MouseWheel = 0.0f;
static GLuint       g_FontTexture = 0;

// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO structure)
// If text or lines are blurry when integrating ImGui in your engine:
// - in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)
void ImGui_ImplSfml_RenderDrawLists(ImDrawData* draw_data)
{
    // We are using the OpenGL fixed pipeline to make the example code simpler to read!
    // A probable faster way to render would be to collate all vertices from all cmd_lists into a single vertex buffer.
    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, vertex/texcoord/color pointers.
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_TEXTURE_2D);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context

    // Setup orthographic projection matrix
    const float width = ImGui::GetIO().DisplaySize.x;
    const float height = ImGui::GetIO().DisplaySize.y;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, +1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Render command lists
    #define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->VtxBuffer.front();
        const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();
        glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, pos)));
        glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, uv)));
        glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, col)));

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback)
            {
                pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                glScissor((int)pcmd->ClipRect.x, (int)(height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
                glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer);
            }
            idx_buffer += pcmd->ElemCount;
        }
    }
    #undef OFFSETOF

    // Restore modified state
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

static const char* ImGui_ImplSfml_GetClipboardText()
{
	// NO CLIPBOARD SUPPORT IN SFML. WINDOWS IMPLEMENTATION INSTEAD
#ifdef _WIN32
	return (char*)GetClipboardData(CF_TEXT);
#else
	return NULL;
#endif
}

static void ImGui_ImplSfml_SetClipboardText(const char* text)
{
#ifdef _WIN32
    SetClipboardData(CF_TEXT, (HANDLE)text);
#endif
}

bool ImGui_ImplSfml_ProcessEvent(sf::Event* event)
{
    ImGuiIO& io = ImGui::GetIO();
    switch (event->type)
    {
	case sf::Event::MouseWheelScrolled:
        {
            if (event->mouseWheelScroll.delta > 0)
                g_MouseWheel = 1;
            if (event->mouseWheelScroll.delta < 0)
                g_MouseWheel = -1;
            return true;
        }
	case sf::Event::MouseButtonPressed:
        {
            if (event->mouseButton.button == sf::Mouse::Left) g_MousePressed[0] = true;
            if (event->mouseButton.button == sf::Mouse::Right) g_MousePressed[1] = true;
            if (event->mouseButton.button == sf::Mouse::Middle) g_MousePressed[2] = true;
            return true;
        }
	case sf::Event::TextEntered:
        {
            ImGuiIO& io = ImGui::GetIO();
			io.AddInputCharacter(event->text.unicode);
            return true;
        }
	case sf::Event::KeyPressed:
    case sf::Event::KeyReleased:
        {
            int key = event->key.code;
            io.KeysDown[key] = (event->type == sf::Event::KeyPressed);
            io.KeyShift = event->key.shift;
            io.KeyCtrl = event->key.control;
            io.KeyAlt = event->key.alt;
            return true;
        }
    }
    return false;
}

bool ImGui_ImplSfml_CreateDeviceObjects()
{
    ImGuiIO& io = ImGui::GetIO();

    // Build texture
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);

    // Create texture
    glGenTextures(1, &g_FontTexture);
    glBindTexture(GL_TEXTURE_2D, g_FontTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);

    // Store our identifier
    io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;

    // Cleanup (don't clear the input data if you want to append new fonts later)
	io.Fonts->ClearInputData();
	io.Fonts->ClearTexData();

    return true;
}

void    ImGui_ImplSfml_InvalidateDeviceObjects()
{
    if (g_FontTexture)
    {
        glDeleteTextures(1, &g_FontTexture);
        ImGui::GetIO().Fonts->TexID = 0;
        g_FontTexture = 0;
    }
}

bool    ImGui_ImplSfml_Init(sf::Window* window)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeyMap[ImGuiKey_Tab] = sf::Keyboard::Tab;                     // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
    io.KeyMap[ImGuiKey_LeftArrow] = sf::Keyboard::Left;
    io.KeyMap[ImGuiKey_RightArrow] = sf::Keyboard::Right;
    io.KeyMap[ImGuiKey_UpArrow] = sf::Keyboard::Up;
    io.KeyMap[ImGuiKey_DownArrow] = sf::Keyboard::Down;
    io.KeyMap[ImGuiKey_PageUp] = sf::Keyboard::PageUp;
    io.KeyMap[ImGuiKey_PageDown] = sf::Keyboard::PageDown;
    io.KeyMap[ImGuiKey_Home] = sf::Keyboard::Home;
    io.KeyMap[ImGuiKey_End] = sf::Keyboard::End;
    io.KeyMap[ImGuiKey_Delete] = sf::Keyboard::Delete;
    io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::BackSpace;
    io.KeyMap[ImGuiKey_Enter] = sf::Keyboard::Return;
    io.KeyMap[ImGuiKey_Escape] = sf::Keyboard::Escape;
    io.KeyMap[ImGuiKey_A] = sf::Keyboard::A;
    io.KeyMap[ImGuiKey_C] = sf::Keyboard::C;
    io.KeyMap[ImGuiKey_V] = sf::Keyboard::V;
    io.KeyMap[ImGuiKey_X] = sf::Keyboard::X;
    io.KeyMap[ImGuiKey_Y] = sf::Keyboard::Y;
    io.KeyMap[ImGuiKey_Z] = sf::Keyboard::Z;
	
    io.RenderDrawListsFn = ImGui_ImplSfml_RenderDrawLists;   // Alternatively you can set this to NULL and call ImGui::GetDrawData() after ImGui::Render() to get the same ImDrawData pointer.
    io.SetClipboardTextFn = ImGui_ImplSfml_SetClipboardText;
    io.GetClipboardTextFn = ImGui_ImplSfml_GetClipboardText;
	
#ifdef _WIN32
    io.ImeWindowHandle = window->getSystemHandle();
#endif

	g_Time.restart();

    return true;
}

void ImGui_ImplSfml_Shutdown()
{
    ImGui_ImplSfml_InvalidateDeviceObjects();
    ImGui::Shutdown();
}

void ImGui_ImplSfml_NewFrame(sf::Window* window)
{
    if (!g_FontTexture)
        ImGui_ImplSfml_CreateDeviceObjects();

    ImGuiIO& io = ImGui::GetIO();

    // Setup display size (every frame to accommodate for window resizing)
    sf::Vector2u windowSize = window->getSize();
    io.DisplaySize = ImVec2((float)windowSize.x, (float)windowSize.y);

    // Setup time step
    io.DeltaTime = g_Time.restart().asSeconds();

    // Setup inputs
    // (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    io.MousePos = ImVec2((float)mousePosition.x, (float)mousePosition.y);   // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
   
	io.MouseDown[0] = g_MousePressed[0] || sf::Mouse::isButtonPressed(sf::Mouse::Left);		// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
	io.MouseDown[1] = g_MousePressed[1] || sf::Mouse::isButtonPressed(sf::Mouse::Right);
	io.MouseDown[2] = g_MousePressed[2] || sf::Mouse::isButtonPressed(sf::Mouse::Middle);
    g_MousePressed[0] = g_MousePressed[1] = g_MousePressed[2] = false;

    io.MouseWheel = g_MouseWheel;
    g_MouseWheel = 0.0f;

    // Hide OS mouse cursor if ImGui is drawing it
    window->setMouseCursorVisible(io.MouseDrawCursor ? 0 : 1);

    // Start the frame
    ImGui::NewFrame();
}