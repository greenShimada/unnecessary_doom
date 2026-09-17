#pragma once
#include <doom/header.h>

class Window {
 private:
  GLFWwindow* window;

 public:
  Window(const char* title);
  ~Window();  // sintaxe do quinto dos infernos
  GLFWwindow* getWindow();
};
