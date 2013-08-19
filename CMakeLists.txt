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

include_directories("${PROJECT_BINARY_DIR}")

add_library(gui ${SOURCES})
add_executable(sdlgui main.cpp)
target_link_libraries(sdlgui gui)
