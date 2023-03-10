#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position) {
    this->position = position;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = -90.0f;
    pitch = 0.0f;
    movementSpeed = 2.5f;
    mouseSensitivity = 0.1f;
    zoom = 45.0f;
    updateVectors();
}

void Camera::update(float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    if (Keyboard::isKeyDown(GLFW_KEY_W)) {
        position += front * velocity;
    }

    if (Keyboard::isKeyDown(GLFW_KEY_S)) {
        position -= front * velocity;
    }

    if (Keyboard::isKeyDown(GLFW_KEY_A)) {
        position -= right * velocity;
    }

    if (Keyboard::isKeyDown(GLFW_KEY_D)) {
        position += right * velocity;
    }

    if (Keyboard::isKeyDown(GLFW_KEY_SPACE)) {
        position += worldUp * velocity;
    }

    if (Keyboard::isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
        position -= worldUp * velocity;
    }

    if (Mouse::isButtonDown(GLFW_MOUSE_BUTTON_RIGHT)) {
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        yaw += Mouse::dx * mouseSensitivity;
        pitch += -Mouse::dy * mouseSensitivity;

        if (pitch > 89.0f) {
            pitch = 89.0f;
        } else if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        updateVectors();
    } else {
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (Mouse::scrollY != 0.0f) {
        zoom -= Mouse::scrollY;

        if (zoom < 1.0f) {
            zoom = 1.0f;
        } else if (zoom > 45.0f) {
            zoom = 45.0f;
        }
    }
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::updateVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
