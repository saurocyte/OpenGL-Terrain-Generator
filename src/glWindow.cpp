#include <glWindow.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <sys.hpp>
#include <mesh.hpp>
#include <drawable.hpp>

auto Window::mouseCallback(GLFWwindow *win, double xpos, double ypos) {
	Window *window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    //std::cout << "INFO::WINDOW::CURSOR_POSITION " << window -> mXPos << " " << window -> mYPos << std::endl;
    window -> mXPos = xpos;
    window -> mYPos = ypos;
};

Window::Window(unsigned const x, unsigned const y)
{
    windowPtr = glfwCreateWindow(800, 600, "123", NULL, NULL);
    glfwMakeContextCurrent(windowPtr);
    glfwSetWindowUserPointer(windowPtr, this);
    glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(windowPtr, mouseCallback);
    // Shit
    gladInit();
    glEnable(GL_DEPTH_TEST);
    // Error manager?
    if (windowPtr == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
    }
}

void Window::makeResizeable()
{
    auto f = [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    };
    glfwSetFramebufferSizeCallback(windowPtr, f);
}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(windowPtr);
}

void Window::display() const
{
    if (buffType == Window::BufferingType::Double)
        glfwSwapBuffers(windowPtr);
    else if (buffType == Window::BufferingType::Single) {
        glFlush();
    }
}

void Window::clear(glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)) const
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setDrawMode(Window::DrawMode mode)
{
    switch (mode)
    {
    case Wireframe:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case Polys:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    }
}

void Window::setBufferingType(BufferingType type) {
    buffType = type;
}

void Window::draw(Drawable *drawable) {
    drawable -> draw(this);
}

void Window::draw(const unsigned int VAO, unsigned int verticiesCount) {
    if (VAO != state.VAO) {
        state.VAO = VAO;
        glBindVertexArray(VAO);
    }
    glDrawArrays(GL_TRIANGLES, 0, verticiesCount);
}

// Polls WINDOW events
void Window::pollEvents() {
    glfwPollEvents();
}

bool Window::keyPressed(unsigned int key) {
    return (glfwGetKey(windowPtr, key) == GLFW_PRESS);
}