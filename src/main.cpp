#include <iostream>
#include <math.h>
#include <GLFW\glfw3.h>
#include "globals.h"
#include "light.h"
#include "Renderer.h"
#include "MeshImporter.h"

void resizeCallback(GLFWwindow* window, int width, int height);
void errorCallback(int error, const char* description);
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);

GLFWwindow* window;
float deltaTime, lastFrame;
int width = 1366;
int height = 768;

void setupSponzaScene() 
{
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	//auto model = std::unique_ptr<Model>(new Model("assets/models/sponza/sponza.obj"));
	//model->setPosition(glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	//model->setScale(0.1f);	// it's a bit too big for our scene, so scale it down
	//scene.addModel(std::move(model));

	//std::unique_ptr<Light> dirLight(new DirectionalLight());
	//dirLight->setPosition(glm::vec3(60.0f, 60.0f, 60.0f));
	//scene.addLight(std::move(dirLight));
}

void setupNanosuitScene()
{
	

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	//auto model = std::unique_ptr<Model>(new Model("assets/models/nanosuit/nanosuit.obj"));
	//model->setPosition(glm::vec3(0.0f, -10.0f, 0.0f)); // translate it down so it's at the center of the scene
	//model->setScale(0.2f);
	//scene.addModel(std::move(model));

	//std::unique_ptr<Light> dirLight(new DirectionalLight());
	//dirLight->setPosition(glm::vec3(60.0f, 60.0f, 60.0f));
	//scene.addLight(std::move(dirLight));
}

void setupTeapotScene()
{
	/*glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);*/

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	//auto model = std::unique_ptr<Model>(new Model("assets/models/dragon/dragon.obj"));
	////model->setScale(0.3f);
	//scene.addModel(std::move(model));
}

//void createFbo(GLuint& fbo, GLuint& texture) 
//{
//	GLuint rbo;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	glGenRenderbuffers(1, &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
//	glGenFramebuffers(1, &fbo);
//	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//	{
//		std::cout << "Error: Framebuffer is not complete" << std::endl;
//	}
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}

bool initWindowSystem(const Renderer& r)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwSetErrorCallback(errorCallback);
	window = glfwCreateWindow(width, height, "Fresnel", NULL, NULL);
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

	if (!r.initSystem((LoadProc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	return true;
}

int main() 
{
	Renderer renderer(width, height);
	if (!initWindowSystem(renderer)) 
	{
		return -1;
	}

	MeshImporter importer;
	importer.load("opengl/assets/models/sponza/sponza.obj");
	auto geometries = importer.getMeshes();
	float currentFrame = 0.0f;
	deltaTime = lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window)) 
	{
		currentFrame = glfwGetTime();
		processInput(window);
		
		renderer.drawScene(geometries);
	
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

	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	scene.getCurrentCamera().moveForward();
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	scene.getCurrentCamera().moveBackward();
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	scene.getCurrentCamera().moveLeft();
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	scene.getCurrentCamera().moveRight();

	////fresnel effect
	//if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	//	scene.incBias();
	//if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	//	scene.incScale();
	//if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	//	scene.incPower();
	//if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	//	scene.decBias();
	//if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	//	scene.decScale();
	//if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	//	scene.decPower();if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	scene.getCurrentCamera().moveForward();
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	scene.getCurrentCamera().moveBackward();
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	scene.getCurrentCamera().moveLeft();
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	scene.getCurrentCamera().moveRight();

	////fresnel effect
	//if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	//	scene.incBias();
	//if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	//	scene.incScale();
	//if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	//	scene.incPower();
	//if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	//	scene.decBias();
	//if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	//	scene.decScale();
	//if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	//	scene.decPower();
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) 
{
	//scene.getCurrentCamera().lookAt(xpos+width, ypos+height);
}

void resizeCallback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void errorCallback(int error, const char* description) 
{
	std::cout << error << ":" << description << std::endl;
}