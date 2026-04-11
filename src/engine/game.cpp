#include "game.hpp"

namespace Engine {
  Game::Game() : isRunning(true), map(80, 24) {
    gen.genDungeon(map);

    // Placeholder for spawning
    playerX = 1;
    playerY = 1;
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
    }
  }

  void Game::draw() {
    renderer.clear();

    for (int y = 0; y < map.getHeight(); y++) {
      for (int x = 0; x < map.getWidth(); x++) {
        World::TileType tile = map.getTile(x, y);

        if (tile == World::TileType::Wall) {
          renderer.drawCell(x, y, "\xE2\x96\x88", Renderer::Color::White);
        } else if (tile == World::TileType::Floor) {
          renderer.drawCell(x, y, " ");
        }
      }
    }

    renderer.drawCell(playerX, playerY, "\xE2\x98\xA0", Renderer::Color::Red);
    renderer.render();
  }

  void Game::run() {
    while (isRunning) {
      draw();
      handleInput();
    }
  }
}
