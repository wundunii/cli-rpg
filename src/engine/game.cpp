#include "game.hpp"

namespace RPG::Engine {
  Game::Game() : isRunning(true), playerX(40), playerY(12) {
    // Init by member contructors
  }

  void Game::handleInput() {
    char c = input.getKey();
    switch (c) {
      case 'w': playerY--; break;
      case 's': playerY++; break;
      case 'a': playerX--; break;
      case 'd': playerX++; break;
      case 'q': isRunning = false; break;
    }
  }

  void Game::draw() {
    renderer.clear();
    renderer.drawChar(playerX, playerY, '@');
    renderer.render();
  }

  void Game::run() {
    while (isRunning) {
      draw();
      handleInput();
    }
  }
}
