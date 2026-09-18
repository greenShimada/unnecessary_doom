#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <doom/texture.h>
#include <doom/shader.h>

// Singleton ResourceManager that hosts several funcs to load Textures and
// Shaders
class ResourceManager {
 public:
  // Resource storage
  static std::map<std::string, Shader> Shaders;
  static std::map<std::string, Texture> Textures;

  // Loads and generates a shader program from file loading vertex, fragment and
  // geometry shader
  static Shader LoadShader(const char* vShaderFile, const char* fShaderFile,
                           const char* gShaderFile, std::string name);
  static Shader& GetShader(std::string name);

  // Loads and generates a texture from file
  static Texture LoadTexture(const char* file, bool alpha, std::string name);
  static Texture& GetTexture(std::string name);

  static void Clear();

 private:
  ResourceManager() {}

  static Shader loadShaderFromFile(const char* vShaderFile,
                                   const char* fShaderFile,
                                   const char* gShaderFile = nullptr);
  static Texture loadTextureFromFile(const char* file, bool alpha);
};

#endif
