#include "ScreenManager.h"

Screen* ScreenManager::currentScreen = nullptr;

void ScreenManager::changeScene(Screen* screen) {
    if (currentScreen != nullptr) {
        currentScreen->dispose();
    }

    currentScreen = screen;
    currentScreen->init();
}

void ScreenManager::init() {
    currentScreen->init();
}

void ScreenManager::update(float deltaTime) {
    currentScreen->update(deltaTime);
}

void ScreenManager::render() {
    currentScreen->render();
}

void ScreenManager::dispose() {
    currentScreen->dispose();
}
