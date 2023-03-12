#include "TestScreen.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Window.h"
#include "Model.h"

#include <imgui.h>

#include <iostream>

Shader shader;
Model model;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void TestScreen::init() {
    shader = ResourceManager::loadShader("assets/shaders/shader.vert", "assets/shaders/shader.frag", "shader");
    model.load("assets/models/backpack/backpack.obj");
}

bool showDemo = true;

void TestScreen::update(float deltaTime) {
    ImGui::ShowDemoWindow(&showDemo);

    camera.update(deltaTime);
}

void TestScreen::render() {
    shader.use();

    glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), static_cast<float>(Window::width) / Window::height, 0.1f, 100.0f);
    glm::mat4 view = camera.getViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setMat4("model", modelMatrix);

    model.draw(shader);
}

void TestScreen::dispose() {

}
