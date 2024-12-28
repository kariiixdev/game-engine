#include "graphics.h"

// Specify the shader buffer size
const uint32_t SHADER_BUFFER_SIZE = 255U;

// Vertex buffer and array objects
uint32_t VBO, VAO, EBO, shaderProgram;

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
            char c = 0;     // Temporary variable to store each character read from the shader source code
            uint32_t i = 0; // Index variable to track the position while iterating through the shader source code

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

void createOpenGLContext(SDL_Window *window)
{
    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // OpenGL context initialization
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (glContext == NULL)
        exit(EXIT_FAILURE);

    // Make the OpenGL context current
    SDL_GL_MakeCurrent(window, glContext);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
        exit(EXIT_FAILURE);

    // Predefined vertices for drawing triangle
    float_t verts[] = {
        -.5f, .5f,
        -.5f, -.5f,
        .0f, -.5f,
        .0f, .5f};

    // Predefined indices for index buffer
    uint32_t indices[] = {
        0, 1, 2,
        2, 3, 0};

    // Create shader objects and shader program
    uint32_t vertShader = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    shaderProgram = glCreateProgram();

    // Load the shaders source code
    const char *vertShaderSrc = loadShader("../shaders/shader.vert");
    const char *fragShaderSrc = loadShader("../shaders/shader.frag");

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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float_t), (void *)0);
    glEnableVertexAttribArray(0);

    // Bind a vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void update(SDL_Window *window)
{
    glClearColor(0.f, 0.f, 1.f, 1.f);                    // Set the screen color to blue
    glClear(GL_COLOR_BUFFER_BIT);                        // Clear screen
    glUseProgram(shaderProgram);                         // Use defined shader program
    glBindVertexArray(VAO);                              // Bind vertex array object
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw Triangle to the screen
    SDL_GL_SwapWindow(window);                           // Swap buffers
}

void cleanup()
{
    // Delete the VAO, buffer objects and shaderProgram
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}
