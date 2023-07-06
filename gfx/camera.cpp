#include "camera.h"

am::gfx::Camera::Camera() {
    this->position = { 0,0,0,0 };
    this->target = { 0,0,0,0 };
    this->upVector = { 0,1,0,0 };
    direction = target - position;
    speed = 0.1;
}

am::gfx::Camera::Camera(glm::vec4 pos, glm::vec4 target, glm::vec4 up)
{
    this->position = pos;
    this->target = target;
    this->upVector = up;
    direction = target - position;
    speed = 0.1;
}


void am::gfx::Camera::moveForward()
{
    position += direction * speed;
    direction = target - position;
}

void am::gfx::Camera::moveBack()
{
    position -= direction * speed;
    direction = target - position;
}

void am::gfx::Camera::moveLeft()
{
    glm::vec3 slide_vector = glm::cross(glm::vec3(direction), glm::vec3(upVector)) * speed;
    position -= glm::vec4(slide_vector, 1);
    target -= glm::vec4(slide_vector,1);
    direction = target - position;

}

void am::gfx::Camera::moveRight()
{
    glm::vec3 slide_vector = glm::cross(glm::vec3(direction), glm::vec3(upVector)) * speed;
    position += glm::vec4(slide_vector, 1);
    target += glm::vec4(slide_vector, 1);
    direction = target - position;
}

void am::gfx::Camera::moveUp()
{
    glm::vec3 slide_vector = glm::normalize(glm::cross(glm::vec3(direction), glm::vec3(upVector)));
    glm::vec3 upDirection = glm::cross(glm::vec3(direction), slide_vector) * speed;
    position -= glm::vec4(upDirection, 0.0);
    target -= glm::vec4(upDirection, 0.0);
    direction = target - position;
}

void am::gfx::Camera::moveDown()
{
    glm::vec3 slide_vector = glm::normalize(glm::cross(glm::vec3(direction), glm::vec3(upVector)));
    glm::vec3 upDirection = glm::cross(glm::vec3(direction), slide_vector) * speed;
    position += glm::vec4(upDirection, 0.0);
    target += glm::vec4(upDirection, 0.0);
    direction = target - position;
}

void am::gfx::Camera::setSpeed(float s)
{
    speed = s;
}

void am::gfx::Camera::setPosition(glm::vec4 p)
{
    position = p;
    direction = target - position;
}

void am::gfx::Camera::setTarget(glm::vec4 t)
{
    target = t;
    direction = target - position;
}

glm::vec4 am::gfx::Camera::getPosition() {
    return position;
}

glm::vec4 am::gfx::Camera::getTarget() {
    return target;
}

glm::vec4 am::gfx::Camera::getUpVector() {
    return upVector;
}

glm::vec4 am::gfx::Camera::getDirection() {
    return direction;
}

void am::gfx::Camera::updateDirection()
{
    direction = target - position;
}
