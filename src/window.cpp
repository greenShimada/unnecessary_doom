#include <doom/window.hpp>
#include <stdexcept>

Window::Window(const char* title) {
  if (!glfwInit()) {
    throw std::runtime_error("Falha ao inicializar o GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Falha ao criar janela");
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  if (!gladLoaderLoadGL()) {
    glfwTerminate();
    throw std::runtime_error("Erro carregando GLAD");
  }
}

Window::~Window() {
  if (window) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();
}

GLFWwindow* Window::getWindow() { return window; }
