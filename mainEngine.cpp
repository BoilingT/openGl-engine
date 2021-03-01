#include "mainEngine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* VERTEX_SHADER_PATH = "shaders/vertexshader.shader";
const char* FRAGMENT_SHADER_PATH = "shaders/fragmentshader.shader";


float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};


unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

float translation[4][4]{
	   {1, 0, 0, 0.5f},
	   {0, 1, 0, 0.2f},
	   {0, 0, 1, 0},
	   {0, 0, 0, 1}
};

float scale[4][4]{
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
};

Matrix<float, 4, 4>* translationMatrix = new Matrix<float, 4, 4>(translation);

Matrix<float, 4, 4>* scaleMatrix = new Matrix<float, 4, 4>(scale);

Matrix<float, 4, 4>* newTranslationMatrix = new Matrix<float, 4, 4>();

Shader* myShader = nullptr;

unsigned int VBO, VAO, EBO;
unsigned int texture1, texture2;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //Change the viewport to the set width and height
}
void mainEngine::run() {
	init();
	createBuffers();
	createShaders();
	createTextures();



	fpsTimeHandler.setTimeStart();
	//This runs while the window has not gotten the instructions to close

	/*
	Matrix<float, 4, 4> myMatrix(m1);
	cout << myMatrix.toString() << endl;
	Matrix<float, 4, 4>* myTransposedMatrix = myMatrix.Transposed();
	cout << myTransposedMatrix->toString() << endl;
	delete myTransposedMatrix;*/

	float A[3][2] = {
			{1, 3},
			{4, -1},
			{-5, 10}
	};

	float B[2][2] = {
			{2, 1},
			{-8, 6}
	};

	/*Matrix<float, 3, 2> mA(A);
	Matrix<float, 2, 2>* mB = new Matrix<float, 2, 2>(B);
	Matrix<float, 3, 2>* resultMat = mA.MatrixMult(mB);
	cout << resultMat->toString() << endl;
	delete resultMat;
	delete mB;*/

	*newTranslationMatrix = *translationMatrix->MatrixMult<4, 4>(scaleMatrix);


	cout << "new: " << translationMatrix->toString() << endl;

	delete translationMatrix;
	delete scaleMatrix;
	while (!glfwWindowShouldClose(window))
	{
		mainLoop();

	}
	cleanup();
}

void mainEngine::init() {

	//Set framerate
	fileHandler file;
	string fileContent;
	if (file.readFile("options.txt", fileContent))
	{
		try
		{
			FRAMES_PER_SECOND_CAP = stof(fileContent);
		}
		catch (const std::exception&)
		{
			cout << "Could not find settings file" << endl;
			file.writeFile("options.txt", to_string(FRAMES_PER_SECOND_CAP));
		}
	}

	//Initialize opengl so that the functions can be used
	glfwInit();

	//Create the window
	Window windowHandler(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, NULL, NULL);
	window = windowHandler.window;

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

	//Every time the window is resized this will run.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void mainEngine::createBuffers() {
#pragma region Vertex

	//A vertex buffer object (VBO) stores all vertex information that will be sent to the graphics card.
	//A vertex array object stores:
	//* Calls to glEnableVertexAttribArray or glDisableVertexAttribArray.
	//* Vertex attribute configurations via glVertexAttribPointer.
	//* Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer.


	//The buffer has a unique id. So we generate one with a buffer id.
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	//Bind the newly created vertex buffer object to the GL_ARRAY_BUFFER
	//Copy vertex data into the buffers memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	//Bind the VAO as an vertex array
	glBindVertexArray(VAO);
	//Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Copy indices data into the buffers memory
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
	//From here every calls to the GL_ARRAY_BUFFER target will be used to configure the currently bound buffer (in this case VBO)


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

void mainEngine::createShaders() {
//The GPU has now the vertex data and the instructions on how it should process the vertex data within a vertex and fragment shader.
//Next OpenGl has to understand how it should interpret the vertex data in memory and how it should connect the vertex data to the vertex shader's attributes.

//Linking Vertex Attributes
//The position data is stored as 32-bit (4 byte) floating point values.
//Each position is composed of 3 of those values.
//There is no space(or other values) between each set of 3 values.The values are tightly packed in the array.
//The first value in the data is at the beginning of the buffer.

//Tell openGl how it should interpret the vertex data (per vertex attribute)
//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//Stride: the space between consecutive vertex attributes.
	//Since the next set of position data is located exactly 3 times the size of a float away we specify that value as the stride.

	//Enable the vertex attribute array
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//int verticesLength = sizeof(vertices) / sizeof(*vertices);
	//int numbVertices = (verticesLength / 3);
	//std::cout << verticesLength / 3 << std::endl;
}

void mainEngine::createTextures() {
#pragma region texture

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Loading the image
	stbi_set_flip_vertically_on_load(true);
	int ImageWidth, ImageHeight, ImageNrChannels;
	unsigned char* imgData = stbi_load("textures/wall.jpg", &ImageWidth, &ImageHeight, &ImageNrChannels, 0);

	//Generate texture
	if (imgData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(imgData);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Load the second image
	//stbi_set_flip_vertically_on_load(true);
	imgData = stbi_load("textures/awesomeface.png", &ImageWidth, &ImageHeight, &ImageNrChannels, 0);
	if (imgData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	//Free the memory
	stbi_image_free(imgData);

	//Set the shader program to use
	myShader = new Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	myShader->use();
	//Setting uniforms
	glUniform1i(glGetUniformLocation(myShader->ID, "texture1"), 0);
	//glUniform1i(glGetUniformLocation(myShader->ID, "texture2"), 1);
	myShader->setInt("texture2", 1);

#pragma endregion
}


void mainEngine::mainLoop() {
	if (myShader == nullptr)
	{
		return;
	}

	//Input
	processInput(window);

	//Render
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//Bind and activate the textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//Process
	float timeValue = glfwGetTime() * 2;
	glm::mat4 trans = glm::mat4(1.0f);

	float rotateZ[4][4] = {
		{cosf(timeValue), -sinf(timeValue), 0, 0},
		{sinf(timeValue), cosf(timeValue), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};

	/*matrix<4,4> rotMatrix(new float[4][4] {
		{cosf(timeValue), -sinf(timeValue), 0, 0},
		{sinf(timeValue), cosf(timeValue), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	});*/

	float rotateY[4][4]{
		{cosf(timeValue), 0, sinf(timeValue), 0},
		{0, 1, 0, 0},
		{-sinf(timeValue), 0, cos(timeValue), 0},
		{0, 0, 0, 1}
	};

	float rotateX[4][4]{
		{1, 0, 0, 0},
		{0, cosf(timeValue), -sinf(timeValue), 0},
		{0, sinf(timeValue), cosf(timeValue), 0},
		{0, 0, 0, 1}
	};


	Matrix<float, 4, 4> rotMatrixZ(rotateZ);
	Matrix<float, 4, 4> rotMatrixY(rotateY);
	Matrix<float, 4, 4> rotMatrixX(rotateX);

	Matrix<float, 4, 4>* rotatedMatrixZ = newTranslationMatrix->MatrixMult<4, 4>(rotMatrixZ);
	//Matrix<float, 4, 4>* rotatedMatrixY = rotatedMatrixZ->MatrixMult<4, 4>(rotMatrixY);
	//Matrix<float, 4, 4>* rotatedMatrixX = rotatedMatrixY->MatrixMult<4, 4>(rotMatrixX);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//transpose
			trans[i][j] = rotatedMatrixZ->getValues()[j][i];
		}
	}
	//cout << resultTranslationMatrix->toString() << endl;

	//delete rotMatrixZ;

	//delete rotatedMatrixX;
	//delete rotatedMatrixY;
	delete rotatedMatrixZ;

	unsigned int transformLocation = glGetUniformLocation(myShader->ID, "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans));

	myShader->use();
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, numbVertices);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Swap buffers and poll IO events
	glfwSwapBuffers(window);
	glfwPollEvents();

	//Calculating and limiting fps
	frame_count++;
	fpsTimeHandler.setTimeEnd();
	double deltaTime = fpsTimeHandler.deltaTime() / 1000000;
	Sleep(1000 / (FRAMES_PER_SECOND_CAP)-deltaTime);
	//double deltaTime = final_time - initial_time;
	if (deltaTime > 0)
	{
		//Set framerate
		int fps = frame_count / deltaTime;
		//fps = frames drawn / time taken in seconds
		if (frame_count >= 100)
		{
			setFPS(window, fps);
			//cout << "FPS: " << fps << " Frames: " << frame_count << " Deltatime: " << deltaTime << endl;
			frame_count = 0;
			fpsTimeHandler.setTimeStart(fpsTimeHandler.endTime);
		}
	}
}

void mainEngine::cleanup() {
	glfwTerminate();
}

void mainEngine::processInput(GLFWwindow* window) {
	//Check if the key is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		//Instruct the window to close
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_D)) {
		angle += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_A)) {
		angle -= 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

