cmake_minimum_required(VERSION 3.22)
project(PROJECT_NAME)

set(CMAKE_CXX_STANDARD 17)

# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
add_executable(${PROJECT_NAME} scripts/main.cpp scripts/Game.cpp scripts/Avatar.cpp scripts/Hazard.cpp scripts/PowerUp.cpp scripts/Background.cpp
        scripts/Game.h
        scripts/Avatar.h
        scripts/Hazard.h
        scripts/PowerUp.h
        scripts/Menu.cpp
        scripts/Menu.h
        scripts/MenuOption.cpp
        scripts/MenuOption.h
        scripts/UI.cpp
        scripts/UI.h)

# --- SDL2 SETUP ---

# Add SDL2_image as a subdirectory
add_subdirectory(SDL2_image)

# Include directories for SDL2 and SDL2_image
include_directories(SDL2_image/include)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

# Link SDL2_image dynamically
target_link_libraries(PROJECT_NAME SDL2_image)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)