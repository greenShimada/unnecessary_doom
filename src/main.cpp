
#include "../include/doom/game.h"
#include "../include/doom/resource_manager.h"
#include "../include/doom/shader.h"

#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

unsigned int SCREEN_WIDTH = 800;
unsigned int SCREEN_HEIGHT = 600;

Game Doom(SCREEN_WIDTH, SCREEN_HEIGHT);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
			SCREEN_WIDTH, 
			SCREEN_HEIGHT, 
			"Unnecessary Doom", 
			nullptr, 
			nullptr
		);

	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoaderLoadGL())
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}	

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// OPENGL CONFIGURATION
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Init game
	Doom.Init();

	// deltaTime
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window)) 
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		Doom.ProcessInput(deltaTime);

		Doom.Update(deltaTime);

		glClearColor(0.1f, 1.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Doom.Render();

		glfwSwapBuffers(window);
	}

	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Doom.Keys[key] = true;
		else if (action == GLFW_RELEASE)
			Doom.Keys[key] = false;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
