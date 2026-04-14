#pragma once
#include "input.hpp"
#include "renderer.hpp"
#include "../world/map.hpp"
#include "../world/gen.hpp"

namespace Engine {

  enum class GameState : uint8_t {
    PauseMenu,
    ViewMap,
    Running
  };

  class Game {
  private:
    bool isRunning;
    GameState currentState;
    int playerX;
    int playerY;

    Input input;
    Renderer::Terminal renderer;
    World::Map map;
    World::Generator gen;

    void handleInput();
    void draw();

    void revealFog();

    void drawUIBorders();
    void drawMinimap();
    void drawFullmap();
    void clearViewport();

  public:
    Game();
    void run();
  };
}
