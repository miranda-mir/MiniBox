cmake_minimum_required(VERSION 3.20)

project(MiniBox VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(TARGET_BINARY minibox)

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${GENERATED_DIR}")

add_compile_options(
    -Wall
    -Wextra
    -std=c++98
    -pedantic
    -fno-unwind-tables
    -fno-exceptions
)

configure_file(
    "${PROJECT_SOURCE_DIR}/MiniBoxConfig.h.in"
    "${GENERATED_DIR}/MiniBoxConfig.h"
    @ONLY
)

add_executable(minibox
    src/MiniBox.cxx
    src/applets.cxx
)

set_target_properties(minibox PROPERTIES
    OUTPUT_NAME "${TARGET_BINARY}"
)

target_include_directories(minibox PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
    "${GENERATED_DIR}"
)

set_property(GLOBAL PROPERTY MINIBOX_APPLET_NAMES "")
set_property(GLOBAL PROPERTY MINIBOX_APPLET_ENTRIES "")
set_property(GLOBAL PROPERTY MINIBOX_APPLET_DECLARATIONS "")
set_property(GLOBAL PROPERTY MINIBOX_APPLET_ENTRY_NAMES "")
set_property(GLOBAL PROPERTY MINIBOX_APPLET_OPTION_NAMES "")

include(cmake/Applets.cmake)
include(cmake/AppletsManifest.cmake)

get_property(APPLET_DECLARATIONS GLOBAL
    PROPERTY MINIBOX_APPLET_DECLARATIONS
)
get_property(APPLET_ENTRIES GLOBAL
    PROPERTY MINIBOX_APPLET_ENTRIES
)

string(JOIN "\n" APPLET_DECLARATIONS_TEXT ${APPLET_DECLARATIONS})
string(JOIN "\n" APPLET_ENTRIES_TEXT ${APPLET_ENTRIES})

configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/AppletRegistry.cxx.in"
    "${GENERATED_DIR}/AppletRegistry.cxx"
    @ONLY
)

target_sources(minibox PRIVATE
    "${GENERATED_DIR}/AppletRegistry.cxx"
    src/libminibox/basename.cxx
)
