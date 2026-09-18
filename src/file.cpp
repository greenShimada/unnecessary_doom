#include <cstdio>
#include <doom/file.hpp>

Files::Files() {
  include = std::string(ROOT_DIR) + "/include/";
  texture = std::string(ROOT_DIR) + "/resources/textures/";
  shaders = std::string(ROOT_DIR) + "/src/shaders/";
};
const char* Files::c_include() const { return include.c_str(); }
const char* Files::c_shaders() const { return shaders.c_str(); }
const char* Files::c_texture() const { return texture.c_str(); }
