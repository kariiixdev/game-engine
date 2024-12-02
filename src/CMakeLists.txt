find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
add_executable(GameEngine
    main.c
)
target_link_libraries(GameEngine ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
