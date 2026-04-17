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

    //Right vector based on direction
    int psx[4] = {1, 0, -1, 0};
    int psy[4] = {0, 1, 0, -1};

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

    void drawText(int x, int y, std::string_view str, Renderer::Color color = Renderer::Color::Default, Renderer::Style style = Renderer::Style::None);
    void drawUIBorders();
    void drawMinimap();
    void drawFullmap();
    void drawPauseMenu();
    void drawPOV();

    template <size_t N>
    void drawBlock(int screenX, int screenY, const std::string_view (&block)[N]) {
      for (size_t y = 0; y < N; y++) {
        std::string_view line = block[y];

        drawText(screenX, screenY + (int)y, line);
      }
    }

    void clearViewport();

  public:
    Game();
    void run();
  };
}
