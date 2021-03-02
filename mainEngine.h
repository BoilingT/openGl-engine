#include <GLFW/glfw3.h>

#include <glad/glad.h> 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <time.h>
#include <Windows.h>

#include "fileHandler.h";
#include "Shader.h"
#include "matrixMath.h"
#include "vectorMath.h"
#include "window.h"
#include "chronoTime.h"

using namespace std;

class mainEngine
{
private:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;
	const char* WINDOW_TITLE = "OpenGL-Graphics";
	float FRAMES_PER_SECOND_CAP = 144.f;
	float angle = 0;

	double initial_time = time(NULL), final_time, frame_count;
	chronoTime fpsTimeHandler;
	
	GLFWwindow* window;

	//Element buffer objects (EBO) stores indices that OpenGL uses to decide what vertices to draw, or in other words called indexed drawing.



	

public:


	mainEngine() {
		
		
	}

	void run();

private:

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

	

	void init();

	void createShaders();

	void createBuffers();

	void createTextures();

	void mainLoop();

	void processInput(GLFWwindow* window);

	void cleanup();

	void setFPS(GLFWwindow* window, int fps) {
		string title = (string)WINDOW_TITLE + "   -   " + to_string(fps) + " FPS";
		glfwSetWindowTitle(window, title.c_str());
	}

	//GLFWframebuffersizefun framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

