#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <math.h>
#include "globals.h"
#include "Scene.h"
#include "light.h"

void resizeCallback(GLFWwindow* window, int width, int height);
void errorCallback(int error, const char* description);
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);

float deltaTime, lastFrame;
int width = 800;
int height = 600;
Scene scene;

int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetErrorCallback(errorCallback);

	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float currentFrame = 0.0f;
	deltaTime = lastFrame = 0.0f;
	scene.init();
	scene.addModel("nanosuit/nanosuit.obj");
	std::unique_ptr<Light> pointLight(new PointLight());
	pointLight->setPosition(glm::vec3(1.2f, 1.0f, 2.0f));
	scene.addLight(std::move(pointLight));



	//TODO: Add Lights to shader
	//TODO: Set Model on shader inside Model object
	//TODO: Set View and Projection on shader
	//TODO: Create a class Material to encapsulate a shader and global parameters like shininess and attach it to a Model object


	while (!glfwWindowShouldClose(window)) 
	{
		currentFrame = glfwGetTime();
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
	
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		scene.getCurrentCamera().moveForward();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		scene.getCurrentCamera().moveBackward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		scene.getCurrentCamera().moveLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		scene.getCurrentCamera().moveRight();
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) 
{
	scene.getCurrentCamera().lookAt(xpos+width, ypos+height);
}

void resizeCallback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void errorCallback(int error, const char* description) 
{
	std::cout << error << ":" << description << std::endl;
}