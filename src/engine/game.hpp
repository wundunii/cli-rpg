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

  enum PlayerD {
    North = 0,
    East = 1,
    South = 2,
    West = 3
  };

  class Game {
  private:
    bool isRunning;
    GameState currState;
    GameState prevState;
    int playerX;
    int playerY;
    //PLayer's Direction
    int playerD;

    Input input;
    Renderer::Terminal renderer;
    World::Map map;
    World::Generator gen;

    void handleInput();
    void draw();

    void revealFog();

    void drawPlayer(int x, int y);
    void drawPlayerSight(int x, int y);

    void drawUIBorders();
    void drawMinimap();
    void drawFullmap();
    void drawPauseMenu();
    
    void clearViewport();

  public:
    Game();
    void run();
  };
}
