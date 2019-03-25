#include <camera.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// Setting front here is kinda useless because of pitch and yaw
Camera::Camera(glm::vec3 _pos, glm::vec3 front, float _speed) : pos(_pos), _front(front), speed(_speed) {}

glm::mat4 Camera::viewMat() const {
    return glm::lookAt(pos, pos + _front, _up);
}

glm::mat4 Camera::projMat() const {
    return glm::perspective(glm::radians(fov), windowWidth / windowHeight, nearPlane, farPlane);
}

void Camera::move(glm::vec3 direction, double deltaTime) {
    pos += speed * direction * static_cast<float>(deltaTime);
}

void Camera::mouseMove(double mxpos, double mypos) {
    if (firstMouse && mxpos != 0 && mypos != 0) {
        lastX = mxpos;
        lastY = mypos;
        firstMouse = false;
    }
    //std::cout << "INFO::CAMERA::FRONT (" << _front.x << " " << _front.y << " " << _front.z << ")" << std::endl;
    float xOffset = mxpos - lastX,
          yOffset = lastY - mypos;
    //std::cout << "lastX: "<< lastX << "\nlastY: " << lastY << "\nxpos: " << mxpos << "\nypos: " << mypos << "\n\n";
    lastX = mxpos;
    lastY = mypos;
    xOffset *= sensitivity;
    yOffset *= sensitivity; 
    yaw += xOffset;
    pitch += yOffset;
    if (pitch > 89.0f) pitch =  89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    
    _front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    _front.y = sin(glm::radians(pitch));
    _front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    _front = glm::normalize(_front);

}

const glm::vec3 Camera::Up = glm::vec3(0.0f, 1.0f, 0.0f); 
const glm::vec3 Camera::Down = glm::vec3(0.0f, -1.0f, 0.0f);
const glm::vec3 Camera::Left = glm::vec3(-1.0f, 0.0f, 0.0f);
const glm::vec3 Camera::Right = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Camera::Forward = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 Camera::Back = glm::vec3(0.0f, 0.0f, -1.0f);