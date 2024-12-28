cmake_minimum_required(VERSION 3.31.1)  # CMake version check
project(GameEngine)                     # Create project "GameEngine"

# Find SDL2 and OpenGL libraries
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

# Define the source files
set(SOURCES
    src/main.c
    src/window.c
    src/graphics.c
)

# Define the header files (optional but recommended for IDEs)
set(HEADERS
    include/window.h
    include/graphics.h
)

# Add the executable target
add_executable(GameEngine ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(GameEngine ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
