#pragma once
#include <GLFW/glfw3.h>

class Window {
public:
    GLFWwindow* window = NULL;

    Window(int width, int height, const char* windowTitle, GLFWmonitor* p_monitor, GLFWwindow* p_share) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(width, height, windowTitle, p_monitor, p_share);
    }

    void makeCurrent() {
        glfwMakeContextCurrent(window);
    }
};