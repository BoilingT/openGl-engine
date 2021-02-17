#include <GLFW/glfw3.h>

#include <glad/glad.h> 
#include <vec.h>
#include <iostream>
#include "fileHandler.h";

//#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
std::string SHADER_PATH = "shaders\\";
std::string VERTEX_SHADER_NAME = "vertexshader.shader";
std::string FRAGMENT_SHADER_NAME = "fragmentshader.shader";
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
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};


unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class mainProgram {
public:
    void run() {
        initWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "openGL-Engine");
        createShaders();
        createShaderProgram();
        createBuffers();
        mainloop();
        cleanup();
    }

private:
    unsigned int fragmentShader, vertexShader, VBO, VAO, EBO, shaderProgram;
    GLFWwindow* window;

    void initWindow(int width, int height, const char* title) {
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

#pragma endregion
    }

    void createShaders() {
        //Vertex shader:
        //The shader object has a unique id. So we generate one with a shader object id.
        //Because we are creating a vertex shader that is why we put in GL_VERTEX_SHADER
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        //Attach the shader source code to the shader object and compile the shader:
        fileHandler fileHandle;
        std::string fileContent;
        fileHandle.readFile((SHADER_PATH + VERTEX_SHADER_NAME), fileContent);
        std::cout << fileContent << std::endl;
        const char* vertexShaderSource = fileContent.c_str();

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
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        //Attach the shader source code to the shader object and compile the shader:
        fileHandle.readFile(((SHADER_PATH + FRAGMENT_SHADER_NAME)), fileContent);
        std::cout << fileContent << std::endl;
        const char* fragmentShaderSource = fileContent.c_str();

        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        //The thing left for the shaders are to link both shader objects into a shader program that will be used for rendering.
        //The shader program will be called every time we want to render
    }

    void createShaderProgram() {
        shaderProgram = glCreateProgram();

        //Attach all the shaders to the program
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        //Link them
        glLinkProgram(shaderProgram);

        //Error checking if the linking failed
        int success;
        char infoLog[512];
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
    }

    void createBuffers() {
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
    }

    void mainloop() {
        //The GPU has now the vertex data and the instructions on how it should process the vertex data within a vertex and fragment shader.
        //Next OpenGl has to understand how it should interpret the vertex data in memory and how it should connect the vertex data to the vertex shader's attributes.

        //Linking Vertex Attributes
        //The position data is stored as 32-bit (4 byte) floating point values.
        //Each position is composed of 3 of those values.
        //There is no space(or other values) between each set of 3 values.The values are tightly packed in the array.
        //The first value in the data is at the beginning of the buffer.

        //Tell openGl how it should interpret the vertex data (per vertex attribute)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        //Stride: the space between consecutive vertex attributes.
        //Since the next set of position data is located exactly 3 times the size of a float away we specify that value as the stride.

        //Enable the vertex attribute array
        glEnableVertexAttribArray(0);


        int verticesLength = sizeof(vertices) / sizeof(*vertices);
        int numbVertices = (verticesLength / 3);
        std::cout << verticesLength / 3 << std::endl;

        //This runs while the window has not gotten the instructions to close
        while (!glfwWindowShouldClose(window)) {
            //Input
            processInput(window);

            //Render
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            //glDrawArrays(GL_TRIANGLES, 0, numbVertices);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            //Swap buffers and poll IO events   
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwTerminate();
    }

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
};

int main() {

    mainProgram app;

    app.run();

    system("pause");
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Change the viewport to the set width and height
}