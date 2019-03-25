#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void glfwFullInit() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void gladInit() {
    if (!gladLoadGL())  {
        std::cout << "Failed to initalize GLAD" << std::endl;
    }
}