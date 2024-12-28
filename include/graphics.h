#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL.h>

const char *loadShader(const char *shaderPath);
void createOpenGLContext(SDL_Window *window);
void update(SDL_Window *window);
void cleanup();

#endif
