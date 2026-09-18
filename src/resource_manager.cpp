#include <doom/resource_manager.h>
#include <GL/gl.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stb/stb_image.h>
#include <doom/shader.h>

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture> ResourceManager::Textures;

Shader ResourceManager::LoadShader(const char* vShaderFile,
                                   const char* fShaderFile,
                                   const char* gShaderFile, std::string name) {
  Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
  return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name) { return Shaders[name]; }

Texture ResourceManager::LoadTexture(const char* file, bool alpha,
                                     std::string name) {
  Textures[name] = loadTextureFromFile(file, alpha);
  return Textures[name];
}

Texture& ResourceManager::GetTexture(std::string name) {
  return Textures[name];
}

void ResourceManager::Clear() {
  for (auto iter : Shaders) glDeleteProgram(iter.second.ID);
  for (auto iter : Textures) glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile,
                                           const char* fShaderFile,
                                           const char* gShaderFile) {
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;

  try {
    // Open files
    std::ifstream vertexShaderFile(vShaderFile);
    std::ifstream fragmentShaderFile(fShaderFile);
    std::stringstream vShadeStream, fShaderStream;

    // read file buffer content into streams
    vShadeStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();

    vertexShaderFile.close();
    fragmentShaderFile.close();

    vertexCode = vShadeStream.str();
    fragmentCode = fShaderStream.str();

    if (gShaderFile != nullptr) {
      std::ifstream geometryShaderFile(gShaderFile);
      std::stringstream gShaderStream;

      gShaderStream << vertexShaderFile.rdbuf();

      geometryShaderFile.close();
      geometryCode = gShaderStream.str();
    }
  } catch (std::exception e) {
    std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
  }

  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();
  const char* gShaderCode = geometryCode.c_str();

  Shader shader;
  shader.Compile(vShaderCode, fShaderCode,
                 gShaderFile != nullptr ? gShaderCode : nullptr);

  return shader;
}

Texture ResourceManager::loadTextureFromFile(const char* file, bool alpha) {
  Texture texture;

  if (alpha) {
    texture.Internal_Format = GL_RGBA;
    texture.Image_Format = GL_RGBA;
  }

  int width, height, nrChannels;

  unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

  texture.Generate(width, height, data);

  stbi_image_free(data);

  return texture;
}
