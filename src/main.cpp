#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "camera.hpp"
#include <iostream>

#include <math.h>
#include "globals.h"
#include "model.h"
#include "shader.hpp"
#include "light.h"
#include <glm/gtc/type_ptr.hpp>

void resizeCallback(GLFWwindow* window, int width, int height);
void errorCallback(int error, const char* description);
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);


Camera camera;
float deltaTime, lastFrame;
int width = 800;
int height = 600;

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

	camera.setPosition(glm::vec3(0.0,0.0,3.0));

	Model object("nanosuit/nanosuit.obj");
	Model object2("nanosuit/nanosuit.obj");
	Shader shader;
	shader.load("basic.vert", "basic.frag");

	//TODO: Add Lights to shader
	//TODO: Set Model on shader inside Model object
	//TODO: Set View and Projection on shader
	//TODO: Create a class Material to encapsulate a shader and global parameters like shininess and attach it to a Model object


	while (!glfwWindowShouldClose(window)) 
	{
		currentFrame = glfwGetTime();
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.use();

		// view/projection transformations
		glm::mat4 projection = camera.getProjection();
		glm::mat4 view = camera.getView();
		shader.setMat4("proj", 1, false, glm::value_ptr(projection));
		shader.setMat4("view", 1, false, glm::value_ptr(view));

		// render the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 1.8f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		shader.setMat4("model", 1, false, glm::value_ptr(model));
		shader.setVec3("cameraPos", camera.getX(), camera.getY(), camera.getZ());
		object.draw(shader);

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		shader.setMat4("model", 1, false, glm::value_ptr(model));

		object2.draw(shader);
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
		camera.moveForward();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.moveBackward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.moveLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.moveRight();
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) 
{
	camera.lookAt(xpos+width, ypos+height);
}

void resizeCallback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void errorCallback(int error, const char* description) 
{
	std::cout << error << ":" << description << std::endl;
}