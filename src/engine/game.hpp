#pragma once
#include "input.hpp"
#include "renderer.hpp"
#include "../world/map.hpp"
#include "../world/gen.hpp"

namespace Engine {
  class Game {
  private:
    bool isRunning;
    int playerX;
    int playerY;

    Input input;
    Renderer::Terminal renderer;
    World::Map map;
    World::Generator gen;

    void handleInput();
    void draw();

    void revealFog();
  public:
    Game();
    void run();
  };
}
