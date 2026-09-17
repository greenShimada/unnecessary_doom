#pragma once
#include <doom/header.h>

class Files {
 private:
  std::string include;
  std::string texture;
  std::string src;
  std::string shaders;

 public:
  const char* c_include() const;
  const char* c_shaders() const;
  const char* c_texture() const;
  Files();
};
