#include "window.h"

SDL_Window *createWindow(const char *title, uint32_t width, uint32_t height)
{
    // Initialization of SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        exit(EXIT_FAILURE); // Quit if video initialization fails
    else
    {
        // SDL window creation
        SDL_Window *window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        // Check if window is NULL
        if (window == NULL)
            exit(EXIT_FAILURE); // Quit if window couldn't be created
        else return window;
    }
}

// Close the program
void close(SDL_Window *window)
{
    SDL_DestroyWindow(window); // Destroy the window
    SDL_Quit();                // Quit the program
}
