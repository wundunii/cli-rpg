#include "game.hpp"

namespace Engine {
  Game::Game() : isRunning{true}, currState{GameState::Running}, prevState(GameState::Running), map{63, 15} {
    gen.genDungeon(map);

    //Spawn player on random Cell
    do {
      playerX = gen.randomInt(1, 62);
      playerY = gen.randomInt(1, 14);
    } while (map.getTile(playerX, playerY) != World::TileType::Floor);
    revealFog();

    //TODO: player should face TileType::Floor at spawn.
    playerD = PlayerD::North;
  }

  //Change in playerX and playerY based on direction
  int pdx[] = {0, 1, 0, -1};
  int pdy[] = {-1, 0, 1, 0};

  void Game::handleInput() {
    char c = input.getKey();

    int nextX = playerX;
    int nextY = playerY;

    if (currState == GameState::Running) {

      switch (c) {
        case 'w': {
                    nextX += pdx[playerD];
                    nextY += pdy[playerD];
                    break;
                  }
        case 's': {
                    nextX -= pdx[playerD];
                    nextY -= pdy[playerD];
                    break;
                  }
        case 'a': playerD = (playerD - 1 + 4) % 4; break;
        case 'd': playerD = (playerD + 1) % 4; break;
        case 'p': currState = GameState::PauseMenu; break;
        case 'm': currState = GameState::ViewMap; break;
      }

      //Only update postion if target tile is Floor
      if (map.getTile(nextX, nextY) == World::TileType::Floor) {
        playerX = nextX;
        playerY = nextY;
        revealFog();
      }
    } else if (currState == GameState::PauseMenu) {
        switch (c) {
          case 'p': currState = GameState::Running; break;
          case 'm': currState = GameState::ViewMap; break;
          case 'q': isRunning = false; break;
      }
    } else if (currState == GameState::ViewMap) {
      switch (c) {
          case 'm': currState = GameState::Running; break;
          case 'p': currState = GameState::PauseMenu; break;
      }
    }
  }

  void Game::drawPlayer(int x, int y) {
    switch (playerD) {
      case 0: renderer.drawCell(x, y, "^", Renderer::Color::Red, Renderer::Style::Bold); break;
      case 1: renderer.drawCell(x, y, ">", Renderer::Color::Red, Renderer::Style::Bold); break;
      case 2: renderer.drawCell(x, y, "v", Renderer::Color::Red, Renderer::Style::Bold); break;
      case 3: renderer.drawCell(x, y, "<", Renderer::Color::Red, Renderer::Style::Bold); break;
    }
  }

  void Game::drawPlayerSight(int x, int y) {
    int sightX = pdx[playerD];
    int sightY = pdy[playerD];

    World::TileType tile = map.getTile(playerX + sightX, playerY + sightY);

    if (tile == World::TileType::Wall) {
      renderer.drawCell(x + sightX, y + sightY, "▓");
    } else if (tile == World::TileType::Floor) {
      renderer.drawCell(x + sightX, y + sightY, " ");
    }
  }

  void Game::revealFog() {
    //Reveal 3x3 around player
    for (int dy = -1; dy <= 1; dy++) {
      for (int dx = -1; dx <= 1; dx++) {
        map.setExplored(playerX + dx, playerY + dy, true);
      }
    }
  }

  void Game::drawUIBorders() { //TODO: Need to be more dynamic?
    using namespace Renderer;
    //Left Side: Combat Log and View Port 62x15
    renderer.drawCell(0, 0, "╔═══════════════════════════════════════════════════════════════╗", Color::White);
    for (int i = 1; i < 21; i++) {
      renderer.drawCell(0, i, "║", Color::White);
      renderer.drawCell(64, i, "║", Color::White);
      renderer.drawCell(65, i, "║", Color::White);
      renderer.drawCell(79, i, "║", Color::White);
    }
    renderer.drawCell(1, 5, "═══════════════════════════════════════════════════════════════", Color::White);
    renderer.drawCell(0, 21, "╠═══════════════════════════════════════════════════════════════╣", Color::White);
  
    //Right Side
    renderer.drawCell(65, 0, "╔═════════════╗", Color::White);
    renderer.drawCell(66, 5, "═════════════", Color::White);
    renderer.drawCell(66, 11, "═════════════", Color::White);
    renderer.drawCell(66, 16, "═════════════", Color::White);
    renderer.drawCell(65, 21, "╠═════════════╣", Color::White);
  
    //Titles
    renderer.drawCell(27, 1, "COMBAT LOG", Color::Cyan, Style::Bold);
    renderer.drawCell(71, 1, "MAP", Color::Cyan, Style::Bold);
    renderer.drawCell(68, 6, "INVENTORY", Color::Cyan, Style::Bold);
    renderer.drawCell(69, 12, "SKILLS", Color::Cyan, Style::Bold);
    renderer.drawCell(70, 17, "STATS", Color::Cyan, Style::Bold);
  
    renderer.drawCell(67, 7, "Gold:", Color::Magenta);
    renderer.drawCell(67, 8, "Heal:", Color::Magenta);
    renderer.drawCell(67, 9, "\xE2\x9A\x94", Color::Magenta);
    renderer.drawCell(67, 10, "\xE2\x9B\x8A", Color::Magenta);
    renderer.drawCell(67, 13, "1.", Color::Magenta);
    renderer.drawCell(67, 14, "2.", Color::Magenta);
    renderer.drawCell(67, 15, "3.", Color::Magenta);
    renderer.drawCell(67, 18, "STR:", Color::Magenta);
    renderer.drawCell(67, 19, "CON:", Color::Magenta);
    renderer.drawCell(67, 20, "INT:", Color::Magenta);
    renderer.drawCell(67, 22, "(P): Pause", Color::Magenta);
    renderer.drawCell(2, 22, "Level:", Color::Magenta);
    renderer.drawCell(18, 22, "HP:", Color::Magenta);
    renderer.drawCell(32, 22, "MP:", Color::Magenta);
    renderer.drawCell(45, 22, "XP:", Color::Magenta);

    //Bottom Border
    renderer.drawCell(0, 22, "║", Color::White);
    renderer.drawCell(79, 22, "║", Color::White);
    renderer.drawCell(64, 22, "║", Color::White);
    renderer.drawCell(65, 22, "║", Color::White);
    renderer.drawCell(0, 23, "╚═══════════════════════════════════════════════════════════════╝╚═════════════╝", Color::White);
  }

  void Game::drawMinimap() {
    using namespace Renderer;
    // Center of minimap (x: 66-78, y: 2-5)
    int mapCenterX = 72;
    int mapCenterY = 3;

    for (int dy = -1; dy <= 1; dy++) {
      for (int dx = -5; dx <= 5; dx++) {
        int worldX = playerX + dx;
        int worldY = playerY + dy;

        if (worldX == playerX && worldY == playerY) {
          drawPlayer(mapCenterX, mapCenterY);
        } else if (map.isExplored(worldX, worldY)) {
          World::TileType tile = map.getTile(worldX, worldY);
          if (tile == World::TileType::Wall) {
            renderer.drawCell(mapCenterX + dx, mapCenterY + dy, "\xE2\x96\x88", Renderer::Color::White);
          } else if (tile == World::TileType::Floor) {
            renderer.drawCell(mapCenterX + dx, mapCenterY + dy, "░");
          }
        }
      }
    }

    drawPlayerSight(mapCenterX, mapCenterY);
  }

  void Game::drawFullmap() {
    // Viewport (x: 1-63, y: 6-20)
    int mapX = 1;
    int mapY = 6;

    for (int y = 0; y < map.getHeight(); y++) {
      for (int x = 0; x < map.getWidth(); x++) {
        World::TileType tile = map.getTile(x, y);
 
        if (map.isExplored(x, y)) {
          if (tile == World::TileType::Wall) {
            renderer.drawCell(x + mapX, y + mapY, "\xE2\x96\x88", Renderer::Color::White);
          } else if (tile == World::TileType::Floor) {
            renderer.drawCell(x + mapX, y + mapY, "░");
          }
        }
      }
    }

    drawPlayer(playerX + mapX, playerY + mapY);
    drawPlayerSight(playerX + mapX, playerY + mapY);
  }

  void Game::drawPauseMenu() {
    renderer.drawCell(29, 6, "PAUSED", Renderer::Color::Red, Renderer::Style::Bold);
    renderer.drawCell(2, 8, "P: Resume", Renderer::Color::Cyan, Renderer::Style::Underline);
    renderer.drawCell(2, 10, "Q: Quit", Renderer::Color::Cyan, Renderer::Style::Underline);
    renderer.drawCell(2, 12, "M: View Full Map", Renderer::Color::Cyan, Renderer::Style::Underline);
  }

  //Cannot use " " because Cells can have strings with length > 1
  //Hacky but works well for now
  void Game::clearViewport() {
    for (int y = 6; y < 21; y++) {
      renderer.drawCell(1, y, "                                                              ");
    }
  }

  void Game::draw() {
    renderer.clear();

    drawUIBorders();
    drawMinimap();

    //Force rendering after switching state to prevent bleeding
    if (currState != prevState) {
      renderer.render();
      clearViewport();
      prevState = currState;
    }

    if (currState == GameState::Running) {
      //Show ViewPort
    } else if (currState == GameState::ViewMap) {
      drawFullmap();
    } else if (currState == GameState::PauseMenu) {
      drawPauseMenu();
    }

    renderer.render();
  }

  void Game::run() {
    while (isRunning) {
      draw();
      handleInput();
    }
  }
}
