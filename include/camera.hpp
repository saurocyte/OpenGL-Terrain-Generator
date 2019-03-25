#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{    
public:
    Camera(glm::vec3 pos, glm::vec3 front, float speed);
    ~Camera() = default;

    glm::vec3 pos;

    float speed;    
    float sensitivity = 0.2;
    float fov = 75;

    auto move(glm::vec3 dir, double deltaTime)              -> void;
    auto mouseMove(double mxpos, double mypos)              -> void;

    // Projection and view matricies for vertex shader
    auto viewMat() const                                    -> glm::mat4;
    auto projMat() const                                    -> glm::mat4;

    // Directions
    inline auto up() {return _up;}
    inline auto down() {return -_up;}
    inline auto front() {return _front;}
    inline auto back() {return -_front;}
    inline auto left() {return glm::normalize(glm::cross(_up, _front));}
    inline auto right() {return -glm::normalize(glm::cross(_up, _front));}

    static const glm::vec3 Up, Down, Left, Right, Forward, Back;

private:
    // Camera position
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 _front;
    float pitch = 0.0f;
    float yaw = -90.0f;

    // For projection matrix
    float windowWidth = 800;
    float windowHeight = 600;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    // Mouse
    float lastX;
    float lastY;
    bool firstMouse = true;
};

#endif
