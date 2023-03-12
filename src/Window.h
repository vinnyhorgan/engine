#pragma once

#include <glad/glad.h> // Needs to be included before glfw3.h
#include <GLFW/glfw3.h>

class Window {
public:
    static int width;
    static int height;

    void run();

private:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};
