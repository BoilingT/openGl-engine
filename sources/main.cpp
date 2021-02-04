#include <GLFW/glfw3.h>

#include <glad/glad.h> 
#include <vec.h>
#include <iostream>
//#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"} \0";

int main() {

#pragma region Creating-Window

    //Initialize opengl so that the functions can be used
	glfwInit();
    //Set the configuration of the window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Create the window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL-Graphics", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Make the context currently as window
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Every time the window is resized this will correct it.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#pragma endregion

    //Verices for a triangle
    float vertices[] = {
    -0.5f, -0.5f, 0.0f, //Left
     0.5f, -0.5f, 0.0f, //Right
     0.0f,  0.5f, 0.0f //Top
    };

#pragma region Vertex-buffer

    //A vertex buffer object (VBO) stores all vertex information that will be sent to the graphics card.
    unsigned int VBO;
    //The buffer has a unique id. So we generate one with a buffer id.
    glGenBuffers(1, &VBO);
    //Bind the newly created buffer to the GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //From here every calls to the GL_ARRAY_BUFFER target will be used to configure the currently bound buffer (in this case VBO)
    
    //Copy vertex data into the buffers memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    //GL_STATIC_DRAW: the data is set only onceand used many times.
    //GL_DYNAMIC_DRAW: the data is changed a lotand used many times.

    //Now the vertex data is stored within the graphics card

    //Process the data with a vertex shader and a fragment shader

    //The vertex shader takes as input a single vertex. 
    //The main purpose of the vertex shader is to transform 3D coordinates into different 3D coordinates
    //The vertex shader allows us to do some basic processing on the vertex attributes.

#pragma endregion

#pragma region Shaders

    //Vertex shader:
    unsigned int vertexShader;
    //The shader object has a unique id. So we generate one with a shader object id.
    //Because we are creating a vertex shader that is why we put in GL_VERTEX_SHADER
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Attach the shader source code to the shader object and compile the shader:
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Error checking if the compilation was successful
    int success;
    char infoLog[512];
    //Checks if the compilation was successful
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //If it wasn't this will run
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //The fragment shader is all about calculating the color output of your pixels

    //The shader object has a unique id. So we generate one with a shader object id.
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //Attach the shader source code to the shader object and compile the shader:
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //The thing left for the shaders are to link both shader objects into a shader program that will be used for rendering.
    //The shader program will be called every time we want to render
    //Shader program

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    //Attach all the shaders to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //Link them
    glLinkProgram(shaderProgram);

    //Error checking if the linking failed
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    //The shaderProgram can be activated by calling glUseProgram(shaderProgram)
    glUseProgram(shaderProgram);
    //Every shader and rendering that call after glUseProgram will now use this program object

    //Because the linking is done the shader objects can be deleted
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

#pragma endregion

    //The GPU has now the vertex data and the instructions on how it should process the vertex data within a vertex and fragment shader.
    //Next OpenGl has to understand how it should interpret the vertex data in memory and how it should connect the vertex data to the vertex shader's attributes.

    //Linking Vertex Attributes

    //Thise runs while the window has not gotten the instructions to close
    while (!glfwWindowShouldClose(window)) {
        //Input
        processInput(window);

        //Render
        glClearColor(255, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        //Swap buffers and poll IO events   
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Change the viewport to the desired width and height
}

void processInput(GLFWwindow* window)
{
    //Check if the key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        //Instruct the window to close
        glfwSetWindowShouldClose(window, true);
}