#include <GLFW/glfw3.h>

#include <glad/glad.h> 
#include <iostream>
#include "fileHandler.h";
#include "Shader.h"
#include "matrixMath.h"
#include "vectorMath.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <string>

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
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
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
    //Set the configuration of the window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Create the window
    GLFWwindow* window;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL-Graphics", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //return -1;
    }

    //Make the context currently as window
    glfwMakeContextCurrent(window);

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
    //Bind the EBO to the GL_ELEMENT_ARRAU_BUFFER
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
        /*matrix<3, 3> zrotationMatrix(new float[3][3]{
            {cosf(timeValue), -sinf(timeValue), 0},
            {sinf(timeValue), cosf(timeValue), 0},
            {0, 0, 1}
        });
        
        matrix<3, 3> yrotationMatrix(new float[3][3]{
            {cosf(timeValue), 0.0f, sinf(timeValue)},
            {0, 1, 0},
            {-sinf(timeValue), 0, cosf(timeValue)}
        });
        
        matrix<3, 3> xrotationMatrix(new float[3][3]{
            {1, 0, 0},
            {0, cosf(timeValue), -sinf(timeValue)},
            {0, sinf(timeValue), cosf(timeValue)}
        });

        auto res = zrotationMatrix.mult<3, 1>(positionMatrix).scale(sin(timeValue));
        std::cout << "x: " << res.values[0][0] << " y: " << res.values[1][0] << " z: " << 0 << std::endl;
        */
        /* 
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); //Getting the uniform variable "ourColor".*/

        //glUniform3f(glGetUniformLocation(myShader.ID, "transform"), res.values[0][0], res.values[1][0], 0.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

        unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        myShader.use();


        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, numbVertices);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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