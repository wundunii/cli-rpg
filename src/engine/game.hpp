#pragma once
#include "input.hpp"
#include "renderer.hpp"

namespace RPG::Engine {
  class Game {
  private:
    bool isRunning;
    int playerX;
    int playerY;

    Input input;
    RPG::Renderer::Terminal renderer;

    void handleInput();
    void draw();

  public:
    Game();
    void run();
  };
}
