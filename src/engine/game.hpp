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
    int playerX;
    int playerY;
    //PLayer's Direction
    int playerD;

    //Change in playerX and playerY based on direction
    int pdx[4] = {0, 1, 0, -1};
    int pdy[4] = {-1, 0, 1, 0};

    Input input;

    Renderer::Terminal renderer;

    //Resolution
    int screenW = renderer.getWidth();
    int screenH = renderer.getHeight();

    World::Map map;
    World::Generator gen;


    void handleInput();
    void draw();

    void revealFog();

    void drawPlayer(int x, int y);
    void drawPlayerSight(int x, int y);

    void drawText(int x, int y, std::string, Renderer::Color color = Renderer::Color::Default, Renderer::Style style = Renderer::Style::None);
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
