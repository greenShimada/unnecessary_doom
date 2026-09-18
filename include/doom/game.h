#pragma once
#ifndef GAME_H
#define GAME_H

enum GameState { GAME_ACTIVE, GAME_PAUSE };

class Game {
 public:
  GameState State;
  bool Keys[1024];
  unsigned int Width, Height;

  Game(unsigned int width, unsigned int height);
  ~Game();

  // Inicia o game state e carrega shaders/texturas/levels....
  void Init();

  // Basically game loop.
  void ProcessInput(float deltaTime);
  void Update(float deltaTime);
  void Render();
};

#endif
