cmake_minimum_required (VERSION 2.8)
project (SDLgui)
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

configure_file (
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_BINARY_DIR}/version.h"
)

set (SOURCES 
    gui/gui.cpp 
    gui/widget.cpp 
    gui/factory.cpp 
    gui/theme.cpp 
    gui/layout/vbox.cpp
    gui/components/button.cpp
)

Find_Package(SDL REQUIRED)
Find_Package(SDL_image REQUIRED)
Find_Package(OpenGL REQUIRED)
Find_Package(Freetype REQUIRED)
Include(./FindFTGL.cmake)

if(NOT SDL_FOUND)
    message (FATAL_ERROR "SDL not found!")
endif(NOT SDL_FOUND)

include_directories(${PROJECT_BINARY_DIR}
                    ${FREETYPE_INCLUDE_DIRS}
                    ${SDL_INCLUDE_DIR}
                    ${OPENGL_INCLUDE_DIR}
                    ${FTGL_INCLUDE_DIR})

add_library(gui ${SOURCES})
target_link_libraries(gui 
    ${SDL_LIBRARY} 
    ${SDLIMAGE_LIBRARY}
    ${OPENGL_LIBRARIES} 
    ${FREETYPE_LIBRARIES}
    ${FTGL_LIBRARY}
    SDLmain)
add_executable(sdlgui WIN32 MACOSX_BUNDLE main.cpp)
target_link_libraries(sdlgui gui)
