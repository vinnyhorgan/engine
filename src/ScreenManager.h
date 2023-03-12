#pragma once

class Screen {
public:
    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void dispose() = 0;
};

class ScreenManager {
public:
    static void changeScene(Screen* screen);
    static void init();
    static void update(float deltaTime);
    static void render();
    static void dispose();

private:
    ScreenManager() { }
    static Screen* currentScreen;
};
