#include "game.hpp"

//Screen Size: x % 5 = 0 && y % 4 = 0 && y >= 28
namespace Engine {
  Game::Game() : isRunning{true}, currState{GameState::Running}, renderer{120, 40}, map{screenW * 4 / 5 - 1, screenH * 3 / 4 - 4} {
    gen.genDungeon(map);

    //Spawn player on random Cell
    do {
      playerX = gen.randomInt(1, 94);
      playerY = gen.randomInt(1, 22);
    } while (map.getTile(playerX, playerY) != World::TileType::Floor);
    revealFog();

    //TODO: player should face TileType::Floor at spawn.
    playerD = PlayerD::North;
  }

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

  void Game::revealFog() {
    //Reveal 3x3 around player
    for (int dy = -1; dy <= 1; dy++) {
      for (int dx = -1; dx <= 1; dx++) {
        map.setExplored(playerX + dx, playerY + dy, true);
      }
    }
  }

  void Game::run() {
    while (isRunning) {
      draw();
      handleInput();
    }
  }
}
