#include "game.hpp"

namespace Engine {
  Game::Game() : isRunning(true), map(62, 15) {
    gen.genDungeon(map);

    // Placeholder for spawning
    while (map.getTile(playerX, playerY) != World::TileType::Floor) {
      playerX = gen.randomInt(1, 61);
      playerY = gen.randomInt(1, 14);
    }
    revealFog();
  }

  void Game::handleInput() {
    char c = input.getKey();
    int nextX = playerX;
    int nextY = playerY;

    switch (c) {
      case 'w': nextY--; break;
      case 's': nextY++; break;
      case 'a': nextX--; break;
      case 'd': nextX++; break;
      case 'q': isRunning = false; break;
    }

    //Only update postion if target tile is Floor
    if (map.getTile(nextX, nextY) == World::TileType::Floor) {
      playerX = nextX;
      playerY = nextY;
      revealFog();
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
    renderer.drawCell(0, 0, "+--------------------------------------------------------------+", Color::White);
    for (int i = 1; i < 21; i++) {
      renderer.drawCell(0, i, "|", Color::White);
      renderer.drawCell(63, i, "|", Color::White);
      renderer.drawCell(65, i, "|", Color::White);
      renderer.drawCell(79, i, "|", Color::White);
    }
    renderer.drawCell(1, 5, "--------------------------------------------------------------", Color::White);
    renderer.drawCell(0, 21, "+--------------------------------------------------------------+", Color::White);
  
    //X offset 45: Minimap, Inventory, Skills
    renderer.drawCell(65, 0, "+-------------+", Color::White);
    renderer.drawCell(66, 5, "-------------", Color::White);
    renderer.drawCell(66, 11, "-------------", Color::White);
    renderer.drawCell(66, 16, "-------------", Color::White);
    renderer.drawCell(65, 21, "+-------------+", Color::White);
  
    //Titles
    renderer.drawCell(27, 1, "COMBAT LOG", Color::Cyan);
    renderer.drawCell(71, 1, "MAP", Color::Cyan);
    renderer.drawCell(68, 6, "INVENTORY", Color::Cyan);
    renderer.drawCell(69, 12, "SKILLS", Color::Cyan);
    renderer.drawCell(70, 17, "STATS", Color::Cyan);
  
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
    renderer.drawCell(0, 22, "|", Color::White);
    renderer.drawCell(79, 22, "|", Color::White);
    renderer.drawCell(63, 22, "|", Color::White);
    renderer.drawCell(65, 22, "|", Color::White);
    renderer.drawCell(0, 23, "+--------------------------------------------------------------+ +-------------+", Color::White);
  }

  void Game::drawMinimap() {
    using namespace Renderer;
    // Center of minimap (x: 66-78, y: 2-5)
    int mapCenterX = 66 + 6;
    int mapCenterY = 3;

    for (int dy = -1; dy <= 1; dy++) {
      for (int dx = -5; dx <= 5; dx++) {
        int worldX = playerX + dx;
        int worldY = playerY + dy;

        if (worldX == playerX && worldY == playerY) {
          renderer.drawCell(mapCenterX + dx, mapCenterY + dy, "\xE2\x98\xA0", Renderer::Color::Red, Renderer::Style::Blink);
        } else if (map.isExplored(worldX, worldY)) {
          World::TileType tile = map.getTile(worldX, worldY);
          if (tile == World::TileType::Wall) {
            renderer.drawCell(mapCenterX + dx, mapCenterY + dy, "\xE2\x96\x88", Renderer::Color::White);
          } else if (tile == World::TileType::Floor) {
            renderer.drawCell(mapCenterX + dx, mapCenterY + dy, " ");
          }
        }
      }
    }
  }

  void Game::drawFullmap() {
    // Viewport (x: 1-62, y: 6-20)
    for (int y = 0; y < map.getHeight(); y++) {
      for (int x = 0; x < map.getWidth(); x++) {
        World::TileType tile = map.getTile(x, y);
    
        if (map.isExplored(x, y)) {
          if (tile == World::TileType::Wall) {
            renderer.drawCell(x + 1, y + 6, "\xE2\x96\x88", Renderer::Color::White);
          } else if (tile == World::TileType::Floor) {
            renderer.drawCell(x + 1, y + 6, " ");
          }
        }
      }
    }

    renderer.drawCell(playerX + 1, playerY + 6, "\xE2\x98\xA0", Renderer::Color::Red, Renderer::Style::Blink);
  }

  void Game::draw() {
    renderer.clear();

    drawUIBorders();
    drawMinimap();
    drawFullmap();
    renderer.render();
  }

  void Game::run() {
    while (isRunning) {
      draw();
      handleInput();
    }
  }
}
