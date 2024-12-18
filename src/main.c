#include "SDL.h"
#include <GL/glew.h>
#include <GL/gl.h>

typedef uint32_t u32;
typedef float_t f32;

const u32 SCREEN_WIDTH = 640U;
const u32 SCREEN_HEIGHT = 480U;
const u32 SHADER_BUFFER_SIZE = 255U;

const char *loadShader(const char *shaderPath)
{
    // Open the shader source file
    FILE *fptr = fopen(shaderPath, "r");
    if (fptr == NULL)
        exit(EXIT_FAILURE);
    else
    {
        // Dynamically allocate memory for the buffer
        char *buffer = (char *)malloc(SHADER_BUFFER_SIZE);
        if (buffer == NULL)
        {
            fclose(fptr);
            exit(EXIT_FAILURE);
        }
        else
        {
            char c = 0; // Temporary variable to store each character read from the shader source code
            u32 i = 0;  // Index variable to track the position while iterating through the shader source code

            // Read the contents of the shader source
            while ((c = fgetc(fptr)) != EOF)
            {
                // Ensure we don't overflow the buffer
                if (i < SHADER_BUFFER_SIZE - 1)
                    buffer[i++] = c;
            }
            buffer[i] = '\0'; // Null terminate the loaded shader source
            fclose(fptr);     // Close the file

            return buffer;
        }
    }
}

int main(int argc, char *argv[])
{
    // Initialization of SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        exit(EXIT_FAILURE); // Quit if video initialization fails
    else
    {
        // Set OpenGL attributes
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Predefined vertices for drawing triangle
        f32 verts[] = {
            -.5f, .5f,
            -.5f, -.5f,
            .0f, -.5f,
            .0f, .5f};

        // Predefined indices for index buffer
        u32 indices[] = {
            0, 1, 2,
            2, 3, 0};

        // SDL window creation
        SDL_Window *window = SDL_CreateWindow(
            "GameEngine demo",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        // Check if window is NULL
        if (window == NULL)
            exit(EXIT_FAILURE); // Quit if window couldn't be created
        else
        {
            // OpenGL context initialization
            SDL_GLContext glContext = SDL_GL_CreateContext(window);
            if (glContext == NULL)
                exit(EXIT_FAILURE);

            // Make the OpenGL context current
            SDL_GL_MakeCurrent(window, glContext);

            // Initialize GLEW
            if (glewInit() != GLEW_OK)
                exit(EXIT_FAILURE);
            else
            {
                // Variables to handle window
                SDL_Event e;
                SDL_bool shouldClose = SDL_FALSE;

                // Create shader objects and shader program
                u32 vertShader = glCreateShader(GL_VERTEX_SHADER);
                u32 fragShader = glCreateShader(GL_FRAGMENT_SHADER);
                u32 shaderProgram = glCreateProgram();

                // Vertex buffer and array objects
                u32 VBO, VAO, EBO;

                // Load the shaders source code
                const char *vertShaderSrc = loadShader("../../shaders/shader.vert");
                const char *fragShaderSrc = loadShader("../../shaders/shader.frag");

                // Replace the source code in shader objects
                glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
                glShaderSource(fragShader, 1, &fragShaderSrc, NULL);

                // Compile the shaders
                glCompileShader(vertShader);
                glCompileShader(fragShader);

                // Attach shaders to shader program
                glAttachShader(shaderProgram, vertShader);
                glAttachShader(shaderProgram, fragShader);

                // Link the shader program
                glLinkProgram(shaderProgram);

                // Delete shader objects
                glDeleteShader(vertShader);
                glDeleteShader(fragShader);

                // Delete the shaders source code
                free((void *)vertShaderSrc);
                free((void *)fragShaderSrc);

                // Generate vertex buffer, index buffer and array objects
                glGenVertexArrays(1, &VAO);
                glGenBuffers(1, &VBO);
                glGenBuffers(1, &EBO);

                // Bind vertex objects
                glBindVertexArray(VAO);
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

                // Create and initialize a buffer objects data store
                glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

                // Define an array of generic vertex attribute data and enable it
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), (void *)0);
                glEnableVertexAttribArray(0);

                // Bind a vertex array object
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

                // Game loop
                while (!shouldClose)
                {
                    // Poll events
                    while (SDL_PollEvent(&e) != 0)
                    {
                        // Exit the program if user wants
                        if (e.type == SDL_QUIT)
                            shouldClose = SDL_TRUE;
                    }

                    glClearColor(0.f, 0.f, 1.f, 1.f);                    // Set the screen color to blue
                    glClear(GL_COLOR_BUFFER_BIT);                        // Clear screen
                    glUseProgram(shaderProgram);                         // Use defined shader program
                    glBindVertexArray(VAO);                              // Bind vertex array object
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw Triangle to the screen
                    SDL_GL_SwapWindow(window);                           // Swap buffers
                }

                // Delete the VAO, buffer objects and shaderProgram
                glDeleteVertexArrays(1, &VAO);
                glDeleteBuffers(1, &VBO);
                glDeleteBuffers(1, &EBO);
                glDeleteProgram(shaderProgram);
            }
        }

        SDL_DestroyWindow(window); // Destroy the window
        SDL_Quit();                // Quit the program
        return 0;
    }
}