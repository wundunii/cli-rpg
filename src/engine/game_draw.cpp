#include "game.hpp"

namespace Engine {
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


    for (int dy = -1; dy <= 1; dy++) {
      for (int dx = -1; dx <= 1; dx++) {
        //Avoid drawing on top of the player
        if (sightX + dx == 0 && sightY + dy == 0) {
          continue;
        }

        World::TileType tile = map.getTile(playerX + sightX + dx, playerY + sightY + dy);

        if (map.isExplored(playerX + sightX + dx, playerY + sightY + dy)) {
          if (tile == World::TileType::Wall) {
            renderer.drawCell(x + sightX + dx, y + sightY + dy, "█");
          } else if (tile == World::TileType::Floor) {
            renderer.drawCell(x + sightX + dx, y + sightY + dy, "▒");
          }
        }
      }
    }
  }

  void Game::drawUIBorders() {
    using namespace Renderer;

    //Horizontal Lines
    int lines_y[4] = {0, screenH / 4, screenH - 3, screenH - 1};

    for (int y : lines_y) {
      for (int x = 1; x < screenW * 4 / 5; x++) {
        renderer.drawCell(x, y, "═");
      }
      
      for (int x = screenW * 4 / 5 + 2; x < screenW - 1; x++) {
        renderer.drawCell(x, y, "═");
      }
    }

    for (int x = screenW * 4 / 5 + 2; x < screenW - 1; x++) {
        renderer.drawCell(x, screenH / 2 - 1, "═");
        renderer.drawCell(x, screenH * 3 / 4 - 2, "═");
    }

    //Vertical Lines
    int lines_x[4] = {0, screenW * 4 / 5, screenW * 4 / 5 + 1, screenW - 1};
    for (int x : lines_x) {
      for (int y = 1; y < screenH / 4; y++) {
        renderer.drawCell(x, y, "║");
      }
      for (int y = screenH / 4 + 1; y < screenH / 2 - 1 ; y++) {
        renderer.drawCell(x, y, "║");
      }
      for (int y = screenH / 2; y < screenH * 3 / 4 - 2; y++) {
        renderer.drawCell(x, y, "║");
      }
      for (int y = screenH * 3 / 4 - 1; y < screenH - 3; y++) {
        renderer.drawCell(x, y, "║");
      }
      renderer.drawCell(x, screenH - 2, "║");
    }

    //Corners
    renderer.drawCell(0, 0, "╔");
    renderer.drawCell(screenW * 4 / 5, 0, "╗");
    renderer.drawCell(screenW * 4 / 5 + 1, 0, "╔");
    renderer.drawCell(screenW - 1, 0, "╗");

    renderer.drawCell(0, screenH / 4, "╠");
    renderer.drawCell(screenW * 4 / 5, screenH / 4, "╣");
    renderer.drawCell(screenW * 4 / 5 + 1, screenH / 4, "╠");
    renderer.drawCell(screenW - 1, screenH / 4, "╣");

    renderer.drawCell(0, screenH / 2 - 1, "║");
    renderer.drawCell(screenW * 4 / 5, screenH / 2 - 1, "║");
    renderer.drawCell(screenW * 4 / 5 + 1, screenH / 2 - 1, "╠");
    renderer.drawCell(screenW - 1, screenH / 2 - 1, "╣");

    renderer.drawCell(0, screenH * 3 / 4 - 2, "║");
    renderer.drawCell(screenW * 4 / 5, screenH * 3 / 4 - 2, "║");
    renderer.drawCell(screenW * 4 / 5 + 1, screenH * 3 / 4 - 2, "╠");
    renderer.drawCell(screenW - 1, screenH * 3 / 4 - 2, "╣");

    renderer.drawCell(0, screenH - 3, "╠");
    renderer.drawCell(screenW * 4 / 5, screenH - 3, "╣");
    renderer.drawCell(screenW * 4 / 5 + 1, screenH - 3, "╠");
    renderer.drawCell(screenW - 1, screenH - 3, "╣");

    renderer.drawCell(0, screenH - 1, "╚");
    renderer.drawCell(screenW * 4 / 5, screenH - 1, "╝");
    renderer.drawCell(screenW * 4 / 5 + 1, screenH - 1, "╚");
    renderer.drawCell(screenW - 1, screenH - 1, "╝");

    //Texts
    renderer.drawCell(screenW * 2 / 5 - 5, 1, "COMBAT LOG", Color::Cyan, Style::Bold);
    renderer.drawCell(screenW * 9 / 10 - 3, 1, "MAP (M)", Color::Cyan, Style::Bold);
    renderer.drawCell(screenW * 9 / 10 - 4, screenH / 4 + 1, "INVENTORY", Color::Cyan, Style::Bold);
    renderer.drawCell(screenW * 9 / 10 - 4, screenH / 2, "ABILITIES", Color::Cyan, Style::Bold);
    renderer.drawCell(screenW * 9 / 10 - 2, screenH * 3 / 4 - 1, "STATS", Color::Cyan, Style::Bold);

    renderer.drawCell(screenW * 4 / 5 + 3, screenH / 4 + 2, "Gold:", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH / 4 + 3, "Heal:", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH / 4 + 4, "\xE2\x9A\x94", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH / 4 + 5, "\xE2\x9B\x8A", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH / 2 + 1, "1.", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH / 2 + 2, "2.", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH / 2 + 3, "3.", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH * 3 / 4, "STR:", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH * 3 / 4 + 1, "CON:", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH * 3 / 4 + 2, "INT:", Color::Magenta);

    renderer.drawCell(2, screenH - 2, "Level:", Color::Magenta);
    renderer.drawCell(screenW / 5, screenH - 2, "HP:", Color::Magenta);
    renderer.drawCell(screenW * 2 / 5, screenH - 2, "MP:", Color::Magenta);
    renderer.drawCell(screenW * 3 / 5, screenH - 2, "XP:", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH - 2, "(P): Pause", Color::Magenta);
  }

  void Game::drawMinimap() {
    using namespace Renderer;

    // Center of minimap
    int mapCenterX = screenW * 9 / 10;
    int mapCenterY = screenH / 8 + 1;

    for (int dy = -3; dy <= 3; dy++) {
      for (int dx = -9; dx <= 9; dx++) {
        int worldX = playerX + dx;
        int worldY = playerY + dy;

        if (worldX == playerX && worldY == playerY) {
          drawPlayer(mapCenterX, mapCenterY);
        } else if (map.isExplored(worldX, worldY)) {
          World::TileType tile = map.getTile(worldX, worldY);
          if (tile == World::TileType::Wall) {
            renderer.drawCell(mapCenterX + dx, mapCenterY + dy, "▓", Renderer::Color::White);
          } else if (tile == World::TileType::Floor) {
            renderer.drawCell(mapCenterX + dx, mapCenterY + dy, "░");
          }
        }
      }
    }

    drawPlayerSight(mapCenterX, mapCenterY);
  }

  void Game::drawFullmap() {
    // Viewport
    int mapX = 1;
    int mapY = screenH / 4 + 1;

    for (int y = 0; y < map.getHeight(); y++) {
      for (int x = 0; x < map.getWidth(); x++) {
        World::TileType tile = map.getTile(x, y);
 
        if (!map.isExplored(x, y)) {
          if (tile == World::TileType::Wall) {
            renderer.drawCell(x + mapX, y + mapY, "▓", Renderer::Color::White);
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

    renderer.drawCell(screenW * 2 / 5 - 3, screenH / 4 + 1, "PAUSED", Renderer::Color::Red, Renderer::Style::Bold);
    renderer.drawCell(2, screenH / 4 + 2, "P: Resume", Renderer::Color::Cyan, Renderer::Style::Underline);
    renderer.drawCell(2, screenH / 4 + 3, "Q: Quit", Renderer::Color::Cyan, Renderer::Style::Underline);
    renderer.drawCell(2, screenH / 4 + 4, "M: View Full Map", Renderer::Color::Cyan, Renderer::Style::Underline);
  }

  //Hacky, only works for a fixed terminal size
  void Game::clearViewport() {

    /*Cannot use " " because Cells can have strings with length > 1
    for (int y = screenH / 4 + 1; y < screenH - 3; y++) {
      for (int x = 1; x < screenW * 4 / 5; x++) {
        renderer.drawCell(x, y, " ");
      }
    }
    */

    for (int y = screenH / 4 + 1; y < screenH - 3; y++) {
        renderer.drawCell(1, y, "                                                                                               ");
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
      renderer.drawCell(10, 10, "ViewPort here");
    } else if (currState == GameState::ViewMap) {
      drawFullmap();
    } else if (currState == GameState::PauseMenu) {
      drawPauseMenu();
    }

    renderer.render();
  }
}
