#include "Keyboard.h"

std::map<int, bool> Keyboard::keysDown;
std::map<int, bool> Keyboard::keysPressed;

void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == 1) {
        keysDown[key] = true;
        keysPressed[key] = true;
    } else if (action == 0) {
        keysDown[key] = false;
    }
}

void Keyboard::update() {
    keysPressed.clear();
}

bool Keyboard::isKeyDown(int key) {
    return keysDown[key];
}

bool Keyboard::isKeyPressed(int key) {
    return keysPressed[key];
}