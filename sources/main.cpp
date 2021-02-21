#include <GLFW/glfw3.h>

#include <glad/glad.h> 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include <string>

#include "fileHandler.h";
#include "Shader.h"
#include "matrixMath.h"
#include "vectorMath.h"
#include "window.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
std::string VERTEX_SHADER_PATH = "shaders/vertexshader.shader";
std::string FRAGMENT_SHADER_PATH = "shaders/fragmentshader.shader";
/*
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"} \0";
*/

float vertices[] = {
    // positions         // colors
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, // top left 
};


unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

void processInput(GLFWwindow* window)
{
    //Check if the key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        //Instruct the window to close
        glfwSetWindowShouldClose(window, true);


    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

int main() {
    //Initialize opengl so that the functions can be used
    glfwInit();

    //Create the window
    Window windowHandler(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL-Graphics", NULL, NULL);
    GLFWwindow* window = windowHandler.window;

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //return -1;
    }

    //Make the context currently as window
    windowHandler.makeCurrent();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        //return -1;
    }

    //Every time the window is resized this will correct it.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#pragma region Vertex

    //A vertex buffer object (VBO) stores all vertex information that will be sent to the graphics card.
    //A vertex array object stores:
    //* Calls to glEnableVertexAttribArray or glDisableVertexAttribArray.
    //* Vertex attribute configurations via glVertexAttribPointer.
    //* Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer.

    //Element buffer objects (EBO) stores indices that OpenGL uses to decide what vertices to draw, or in other words called indexed drawing.
    unsigned int VBO, VAO, EBO;
    //The buffer has a unique id. So we generate one with a buffer id.
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    //Bind the newly created vertex buffer object to the GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Bind the VAO as an vertex array
    glBindVertexArray(VAO);
    //Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //Copy indices data into the buffers memory
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    //From here every calls to the GL_ARRAY_BUFFER target will be used to configure the currently bound buffer (in this case VBO)

    //Copy vertex data into the buffers memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    //GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    //GL_STATIC_DRAW: the data is set only once and used many times.
    //GL_DYNAMIC_DRAW: the data is changed a lot and used many times.

    //Now the vertex data is stored within the graphics card

    //Process the data with a vertex shader and a fragment shader

    //The vertex shader takes as input a single vertex. 
    //The main purpose of the vertex shader is to transform 3D coordinates into different 3D coordinates
    //The vertex shader allows us to do some basic processing on the vertex attributes.

#pragma endregion

    //The GPU has now the vertex data and the instructions on how it should process the vertex data within a vertex and fragment shader.
    //Next OpenGl has to understand how it should interpret the vertex data in memory and how it should connect the vertex data to the vertex shader's attributes.

    //Linking Vertex Attributes
    //The position data is stored as 32-bit (4 byte) floating point values.
    //Each position is composed of 3 of those values.
    //There is no space(or other values) between each set of 3 values.The values are tightly packed in the array.
    //The first value in the data is at the beginning of the buffer.

    //Tell openGl how it should interpret the vertex data (per vertex attribute)
    //Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //Stride: the space between consecutive vertex attributes.
    //Since the next set of position data is located exactly 3 times the size of a float away we specify that value as the stride.

    //Enable the vertex attribute array
    glEnableVertexAttribArray(0);

    //Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    int verticesLength = sizeof(vertices) / sizeof(*vertices);
    int numbVertices = (verticesLength / 3);
    std::cout << verticesLength / 3 << std::endl;

    Shader myShader(VERTEX_SHADER_PATH.c_str(), FRAGMENT_SHADER_PATH.c_str());

    matrix<3, 1> positionMatrix(new float[3][1]{
        {1},{1},{0}
    });
    //This runs while the window has not gotten the instructions to close
    while (!glfwWindowShouldClose(window)) {
        //Input
        processInput(window);

        //Render
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        float timeValue = glfwGetTime() * 1;

        //Use the shaders
        myShader.use();

        //Bind the vertex array object so that it can be used
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, numbVertices);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Swap buffers and poll IO events   
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    system("pause");
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Change the viewport to the set width and height
}