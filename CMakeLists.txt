cmake_minimum_required(VERSION 3.27)
project(AwesomeWallpaper)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(ICON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/icon.ico")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(AwesomeWallpaper src/main.cpp
        src/kernel/WindowsApi.cpp
        src/kernel/WindowsApi.h
        src/windows/controls/TrayIcon.cpp
        src/windows/controls/TrayIcon.h
        src/resources/resource.h
        src/windows/Application.cpp
        src/windows/Application.h
        src/windows/ConfigurationWindow.cpp
        src/windows/ConfigurationWindow.h
        src/windows/controls/Button.cpp
        src/windows/controls/Button.h
)

# Add resource.rc to the project
add_custom_command(
        TARGET AwesomeWallpaper
        PRE_BUILD
        COMMAND ${CMAKE_RC_COMPILER} -fo ${CMAKE_BINARY_DIR}/resource.res ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/resource.rc
)

target_include_directories(AwesomeWallpaper PUBLIC "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/kernel"
        "${CMAKE_SOURCE_DIR}/windows"
)

# Copy the icon file to the executable directory during build
configure_file(${ICON_FILE} ${CMAKE_BINARY_DIR}/bin/icon.ico COPYONLY)

# Copy the font file to the executable directory during build
configure_file(${ICON_FILE} ${CMAKE_BINARY_DIR}/bin/Roboto-Bold.ttf COPYONLY)

target_link_libraries(AwesomeWallpaper PRIVATE sfml-graphics)
target_compile_features(AwesomeWallpaper PRIVATE cxx_std_17)

install(TARGETS AwesomeWallpaper)

