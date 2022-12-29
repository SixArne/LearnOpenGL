#include "pch.h"
#include <iostream>

#include <VLD/vld.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include <vector>
#include <fstream>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO{}, VBO{};

void CreateTriangle()
{
    std::array<GLfloat, 9> vertices{
        -1.f, -1.f, 0.f,
        1.f, -1.f, 0.f,
        0.f, 1.f, 0.f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
}

std::vector<char> ReadFile(std::string file)
{
    std::ifstream fileStream{};
    fileStream.open(file, std::ios::in | std::ios::ate);
    if (!fileStream.is_open())
    {
        throw std::runtime_error("No such file");
    }
    
    size_t fileSize = (size_t)fileStream.tellg();
    std::vector<char> fileBuffer( fileSize );

    fileStream.seekg(0);

    fileStream.read(fileBuffer.data(), fileSize);

    fileStream.close();

    return fileBuffer;
}

GLint CreateShader(std::string srcFile)
{
    GLint vertexShader{};
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    auto shaderFile = ReadFile(srcFile).data();
    glShaderSource(vertexShader, 1, &shaderFile, nullptr);
    glCompileShader(vertexShader);

    // Validate compilation
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

        throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
    }

    return vertexShader;
}

GLuint CreateShaderProgram(const std::vector<GLint>& shaders)
{
    GLuint shaderProgram{};
    shaderProgram = glCreateProgram();

    for (const GLint shader : shaders)
    {
        glAttachShader(shaderProgram, shader);
    }

    glLinkProgram(shaderProgram);

    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        
        throw std::runtime_error("Failed to link shaders");
    }

    return shaderProgram;
}

int main()
{
    if (!glfwInit())
    {
        glfwTerminate();
    }

    // Set version to 4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);
    if (pWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return -1;
    }

    // Get window buffer information
    int bufferWidth{}, bufferHeight{};
    glfwGetFramebufferSize(pWindow, &bufferWidth, &bufferHeight);

    glfwMakeContextCurrent(pWindow);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;

        glfwDestroyWindow(pWindow);
        glfwTerminate();

        return -1;
    }

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
   
    GLint vertexShader = CreateShader("Shaders/shader.vert");
    GLint fragmentShader = CreateShader("Shaders/shader.frag");

    std::vector<GLint> shaders = { vertexShader, fragmentShader };

    GLuint shaderProgram = CreateShaderProgram(shaders);
    CreateTriangle();

    glUseProgram(shaderProgram);

    // Loop until window closed
    while (!glfwWindowShouldClose(pWindow))
    {
        glfwPollEvents();

        glClearColor(1.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(pWindow);
    }

    glfwDestroyWindow(pWindow);
    glfwTerminate();
    
    for (const GLint shader : shaders)
    {
        glDeleteShader(shader);
    }

    return 0;
}

