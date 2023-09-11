#ifndef CAMERA_H
#define CAMERA_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtx/vector_angle.hpp>

#include "Source/Shader.h"

class Camera
{
public:

    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    int Width;
    int Height;

    float Speed = 0.1f;
    float Sensitivity = 100.0f;

    bool Initial = true;

    // Constructor
    Camera(int Width, int Height, glm::vec3 Position);

    // Methods
    void Matrix(Shader& Shader, const char* Uniform, float FOV, float Near, float Far);
    void Input(GLFWwindow* Window);

};

Camera::Camera(int Width, int Height, glm::vec3 Position) {
    this->Width = Width;
    this->Height = Height;
    this->Position = Position;
}

void Camera::Matrix(Shader& Shader, const char* Uniform, float FOV, float Near, float Far) {
    glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up);
    glm::mat4 projection = glm::perspective(glm::radians(FOV), (float)Width / Height, Near, Far);

    glUniformMatrix4fv(glGetUniformLocation(Shader.ID, Uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Input(GLFWwindow* Window) {

    if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Position += Speed * Orientation;
    }
    if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Position += Speed * -Orientation;
    }
    if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Position += Speed * -glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Position += Speed * glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(Window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Position += Speed * Up;
    }
    if (glfwGetKey(Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        Position += Speed * -Up;
    }
    if (glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        Speed = 0.003f;
    }
    else if (glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        Speed = 0.001f;
    }

    // Handles mouse inputs
    if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (Initial)
        {
            glfwSetCursorPos(Window, Width / 2, Height / 2);
            Initial = false;
        }

        double MouseX;
        double MouseY;
        glfwGetCursorPos(Window, &MouseX, &MouseY);

        float RotationX = Sensitivity * (float)(MouseY - Height / 2) / Height;
        float RotationY = Sensitivity * (float)(MouseX - Width / 2) / Width;

        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-RotationX), glm::normalize(glm::cross(Orientation, Up)));
        if (!(glm::angle(newOrientation, Up) <= glm::radians(5.0f) || glm::angle(newOrientation, glm::vec3(0.0f, -1.0f, 0.0f)) <= glm::radians(5.0f)))
        {
            Orientation = newOrientation;
        }

        Orientation = glm::rotate(Orientation, glm::radians(-RotationY), Up);

        glfwSetCursorPos(Window, Width / 2, Height / 2);
    }
    else if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        Initial = true;
    }

}

#endif