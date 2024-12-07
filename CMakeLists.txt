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
# Include directories for SDL2 and SDL2_image
include_directories(${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/include/SDL2)
include_directories(${CMAKE_SOURCE_DIR}/SDL2_image/include)

# Link directories for SDL2 and SDL2_image
link_directories(${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/lib)
link_directories(${CMAKE_SOURCE_DIR}/SDL2_image/lib)

# Link libraries
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_image)

# Copy assets and DLLs for portability on Windows
if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/bin/SDL2.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/SDL2_image/lib/SDL2_image.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
message("SDL2 Include: ${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/include/SDL2")
message("SDL2_image Include: ${CMAKE_SOURCE_DIR}/SDL2_image/include")
message("SDL2 Link Directory: ${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/lib")
message("SDL2_image Link Directory: ${CMAKE_SOURCE_DIR}/SDL2_image/lib")
