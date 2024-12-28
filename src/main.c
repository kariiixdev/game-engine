#include "window.h"
#include "graphics.h"

int main(int argc, char *argv[])
{
    // SDL window creation
    SDL_Window *window = createWindow("Game Window", 800, 600);
    createOpenGLContext(window);

    // Variables to handle window
    SDL_Event e;
    SDL_bool windowOpen = SDL_TRUE;

    // Game loop
    while (windowOpen)
    {
        // Poll events
        while (SDL_PollEvent(&e) != 0)
        {
            // Exit the program if user wants
            if (e.type == SDL_QUIT)
                windowOpen = SDL_FALSE;
        }
        // Update the window
        update(window);
    }

    // Cleanup and close the program
    cleanup();
    close(window);
    return 0;
}
