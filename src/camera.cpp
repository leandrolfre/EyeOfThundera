#include "camera.hpp"
#include <iostream>
#include "globals.h"

void Camera::move(const glm::vec3 &velocity) 
{
	_position += deltaTime * _speed * velocity;
	//logPosition();
}

void Camera::moveForward()
{
	move(_target);
}

void Camera::moveBackward() 
{
	move(_target * -1.0f);
}

void Camera::moveLeft() 
{
	move(glm::normalize(glm::cross(_target, _up) * -1.0f));
}

void Camera::moveRight() 
{
	move(glm::normalize(glm::cross(_target, _up)));
}

void Camera::lookAt(double x, double y) 
{
	if (_lastXPos <= -1.0f && _lastYPos <= -1.0f)
	{
		_lastXPos = x;
		_lastYPos = y;
	}

	_yaw += (x - _lastXPos) * _sensitivity;
	_pitch += (_lastYPos - y) * _sensitivity;
	_lastXPos = x;
	_lastYPos = y;

	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_target = glm::normalize(front);
	//logPosition();
}

void Camera::logPosition() 
{
	std::cout << "vec(" << _target.x << "," << _target.y << "," << _target.z << ")" << std::endl;
}