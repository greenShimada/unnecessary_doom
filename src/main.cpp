#include <doom/header.h>
#include <doom/shader.h>
#include <doom/window.hpp>
#include <doom/file.hpp>
#include <doom/game.h>
#include <GLFW/glfw3.h>
#include <doom/resource_manager.h>

Game Doom(SCREEN_WIDTH, SCREEN_HEIGHT);

int main() {
  Files files;

  Window window("Unecessary DOOM");
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // OPENGL CONFIGURATION
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Init game
  Doom.Init();

  // deltaTime
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  while (!glfwWindowShouldClose(window.getWindow())) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents();

    Doom.ProcessInput(deltaTime);

    Doom.Update(deltaTime);

    glClearColor(0.1f, 1.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Doom.Render();

    glfwSwapBuffers(window.getWindow());
  }

  ResourceManager::Clear();

  glfwTerminate();
  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS)
      Doom.Keys[key] = true;
    else if (action == GLFW_RELEASE)
      Doom.Keys[key] = false;
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
