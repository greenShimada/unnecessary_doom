#include <doom/game.h>
#include <doom/sprite_renderer.h>
#include <doom/resource_manager.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <doom/file.hpp>

SpriteRenderer* Renderer;

// Construtor
Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

// Desconstrutor
Game::~Game() { delete Renderer; }

void Game::Init() {
  Files files;
  std::string spriteVertexPath = std::string(files.c_shaders()) + "sprite.vs";
  std::string spriteFragPath = std::string(files.c_shaders()) + "sprite.frag";
  std::string awesomeFacePath =
      std::string(files.c_texture()) + "awesomeface.png";

  ResourceManager::LoadShader(spriteVertexPath.c_str(), spriteFragPath.c_str(),
                              nullptr, "sprite");

  // COnfigure shaders
  glm::mat4 projection =
      glm::ortho(0.0f, static_cast<float>(this->Width),
                 static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

  ResourceManager::GetShader("sprite").Use().SetInteger("Image", 0);
  ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

  Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

  ResourceManager::LoadTexture(awesomeFacePath.c_str(), true, "face");
}

void Game::ProcessInput(float deltaTime) {}

// Per Frame
void Game::Update(float deltaTime) {}

void Game::Render() {
  Renderer->DrawSprite(
      ResourceManager::GetTexture("face"), glm::vec3(200.0f, 200.0f, 0.0f),
      glm::vec3(300.0f, 300.0f, 0.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
