#include "Mouse.h"

float Mouse::x = 0.0f;
float Mouse::y = 0.0f;
float Mouse::scrollX = 0.0f;
float Mouse::scrollY = 0.0f;
float Mouse::dx = 0.0f;
float Mouse::dy = 0.0f;
float Mouse::lastX = 0.0f;
float Mouse::lastY = 0.0f;

std::map<int, bool> Mouse::buttonsDown;
std::map<int, bool> Mouse::buttonsPressed;

void Mouse::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    dx = (float)xpos - lastX;
    dy = (float)ypos - lastY;
    lastX = (float)xpos;
    lastY = (float)ypos;
    x = (float)xpos;
    y = (float)ypos;
}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == 1) {
        buttonsDown[button] = true;
        buttonsPressed[button] = true;
    } else if (action == 0) {
        buttonsDown[button] = false;
    }
}

void Mouse::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    scrollX = (float)xoffset;
    scrollY = (float)yoffset;
}

void Mouse::update() {
    dx = 0.0f;
    dy = 0.0f;
    scrollX = 0.0f;
    scrollY = 0.0f;
    buttonsPressed.clear();
}

bool Mouse::isButtonDown(int button) {
    return buttonsDown[button];
}

bool Mouse::isButtonPressed(int button) {
    return buttonsPressed[button];
}
