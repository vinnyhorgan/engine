#pragma once

#include <GLFW/glfw3.h>

#include <map>

class Mouse {
public:
    static float x, y, scrollX, scrollY, dx, dy;
    static std::map<int, bool> buttonsDown;
    static std::map<int, bool> buttonsPressed;

    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void update();
    static bool isButtonDown(int button);
    static bool isButtonPressed(int button);

private:
    static float lastX, lastY;
};
