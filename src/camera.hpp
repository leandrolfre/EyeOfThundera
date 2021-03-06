#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:
	Camera() : _position(0.0f, 0.0f, 0.0f), _target(0.0f, 0.0f, -3.0f), _up(0.0f, 1.0f, 0.0f), 
		_speed(2.5f), _pitch(0.0f), _yaw(-90.0f), _lastXPos(-1.0f), _lastYPos(-1.0f), _sensitivity(0.05f) {};
	~Camera() {};
	glm::mat4x4 getView() { return glm::lookAt(_position, _position + _target, _up); };
	glm::mat4 getProjection() { return glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); };
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void lookAt(double x, double y);
	float getX() { return _position.x; };
	float getY() { return _position.y; };
	float getZ() { return _position.z; };
	void setPosition(glm::vec3 position) { _position = position; }

private:
	float _speed;
	float _pitch;
	float _yaw;
	float _lastXPos;
	float _lastYPos;
	float _sensitivity;
	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _up;

private:
	void move(const glm::vec3 &velocity);
	void logPosition();

};
