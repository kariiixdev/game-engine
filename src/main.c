#include "SDL.h"
#include <GL/gl.h>

typedef uint32_t u32;

const u32 SCREEN_WIDTH = 640U;
const u32 SCREEN_HEIGHT = 480U;
const u32 SHADER_BUFFER_SIZE = 255U;

// TODO: Improve the loadShader function
void loadShader()
{
    // Open the shader source file
    FILE *fptr = fopen("../../shaders/shader.vert", "r");
    if (fptr == NULL)
        exit(1);
    else
    {
        char buffer[SHADER_BUFFER_SIZE]; // Array to hold the entire shader source code as a string
        char c = 0;                      // Temporary variable to store each character read from the shader source code
        u32 i = 0;                       // Index variable to track the position while iterating through the shader source code

        // Read the contents of the shader source
        while ((c = fgetc(fptr)) != EOF)
        {
            // Ensure we don't overflow the buffer
            if (i < SHADER_BUFFER_SIZE - 1)
                buffer[i++] = c;
        }
        buffer[i] = '\0'; // Null-terminate the string
        fclose(fptr);     // Close the file
    }
}

int main(int argc, char *argv[])
{
    // Initialization of SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        exit(-1); // Quit if video initialization fails
    else
    {
        // Set OpenGL attributes
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // SDL window creation
        SDL_Window *window = SDL_CreateWindow(
            "GameEngine demo",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        // Check if window is NULL
        if (window == NULL)
            exit(-1); // Quit if window couldn't be created
        else
        {
            // OpenGL context initialization
            SDL_GLContext *glContext = SDL_GL_CreateContext(window);
            if (glContext == NULL)
                exit(-1);
            else
            {
                // Game loop
                SDL_Event e;
                SDL_bool shouldClose;
                loadShader();
                while (!shouldClose)
                {
                    // Poll events
                    while (SDL_PollEvent(&e) != 0)
                    {
                        glClearColor(1.f, 0.f, 0.f, 1.f); // Set the screen color to red
                        glClear(GL_COLOR_BUFFER_BIT);     // Clear screen
                        SDL_GL_SwapWindow(window);        // Swap buffers

                        if (e.type == SDL_QUIT)
                            shouldClose = SDL_TRUE; // Exit the program if user wants
                    }
                }
            }
        }

        SDL_DestroyWindow(window); // Destroy the window
        SDL_Quit();                // Quit the program
        return 0;
    }
}
