#pragma once

#include <GLFW/glfw3.h>

#include <map>

class Keyboard {
public:
    static std::map<int, bool> keysDown;
    static std::map<int, bool> keysPressed;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void update();
    static bool isKeyDown(int key);
    static bool isKeyPressed(int key);
};
