#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

SDL_Window *createWindow(const char *title, uint32_t width, uint32_t height);
void destroyWindow(SDL_Window *window);
void close(SDL_Window *window);

#endif
