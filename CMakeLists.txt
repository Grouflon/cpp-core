include_directories(src)

# check 64 bit
if (CMAKE_SIZEOF_VOID_P MATCHES 8)
    set( PROJECT_ARCH "x64" )
else()
    set( PROJECT_ARCH "x86" )
endif()

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE CPPCORE_SOURCE_FILES src/*)
file(GLOB_RECURSE AUDIO_SOURCE_FILES extern/audio/*)
file(GLOB_RECURSE GL3W_SOURCE_FILES extern/gl3w/*)
file(GLOB_RECURSE GLM_SOURCE_FILES extern/glm/*)
file(GLOB_RECURSE IMGUI_SOURCE_FILES extern/imgui/*)
file(GLOB_RECURSE JSON_SOURCE_FILES extern/json/*)


list(REMOVE_ITEM IMGUI_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui/imgui_impl_glfw_gl3.cpp")
list(REMOVE_ITEM IMGUI_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui/imgui_impl_glfw_gl3.h")
list(REMOVE_ITEM IMGUI_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui/imgui_impl_sfml.cpp")
list(REMOVE_ITEM IMGUI_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui/imgui_impl_sfml.h")

include_directories(
        extern/audio
        extern/gl3w
        extern/glm
        extern/imgui
        extern/json
        extern/portaudio/include
        extern/SDL2-2.0.4/include
)

add_definitions(-DIMGUI_INCLUDE_IMGUI_USER_H=1)

add_library(
        cpp-core

        STATIC

        ${CPPCORE_SOURCE_FILES}
        ${AUDIO_SOURCE_FILES}
        ${GL3W_SOURCE_FILES}
        ${GLM_SOURCE_FILES}
        ${IMGUI_SOURCE_FILES}
        ${JSON_SOURCE_FILES}
)

target_link_libraries(
        cpp-core

        ${CMAKE_CURRENT_SOURCE_DIR}/portaudio/lib/${PROJECT_ARCH}/${CMAKE_BUILD_TYPE}/portaudio_x86.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/SDL2-2.0.4/lib/${PROJECT_ARCH}/SDL2.lib
)