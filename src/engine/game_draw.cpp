#include "game.hpp"

using namespace Renderer;

namespace Engine {
  void Game::drawPlayer(int x, int y) {
    switch (playerD) {
      case 0: renderer.drawCell(x, y, "^", Color::Red, Style::Bold); break;
      case 1: renderer.drawCell(x, y, ">", Color::Red, Style::Bold); break;
      case 2: renderer.drawCell(x, y, "v", Color::Red, Style::Bold); break;
      case 3: renderer.drawCell(x, y, "<", Color::Red, Style::Bold); break;
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

  void Game::drawText(int x, int y, std::string_view str, Color color, Style style) {
    for (size_t i = 0; i < str.length(); i++) {
      renderer.drawCell(x + i, y, str.substr(i, 1), color, style);
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
    drawText(screenW * 2 / 5 - 5, 1, "COMBAT LOG", Color::Cyan, Style::Bold);
    //drawText(screenW * 9 / 10 - 3, 1, "MAP (M)", Color::Cyan, Style::Bold);
    drawText(screenW * 9 / 10 - 4, screenH / 4 + 1, "INVENTORY", Color::Cyan, Style::Bold);
    drawText(screenW * 9 / 10 - 4, screenH / 2, "ABILITIES", Color::Cyan, Style::Bold);
    drawText(screenW * 9 / 10 - 2, screenH * 3 / 4 - 1, "STATS", Color::Cyan, Style::Bold);

    drawText(screenW * 4 / 5 + 3, screenH / 4 + 2, "Gold:", Color::Magenta);
    drawText(screenW * 4 / 5 + 3, screenH / 4 + 3, "Heal:", Color::Magenta);
    //Unicode symbols have to be drawn with drawCell
    renderer.drawCell(screenW * 4 / 5 + 3, screenH / 4 + 4, "\xE2\x9A\x94", Color::Magenta);
    renderer.drawCell(screenW * 4 / 5 + 3, screenH / 4 + 5, "\xE2\x9B\x8A", Color::Magenta);
    drawText(screenW * 4 / 5 + 3, screenH / 2 + 1, "1.", Color::Magenta);
    drawText(screenW * 4 / 5 + 3, screenH / 2 + 2, "2.", Color::Magenta);
    drawText(screenW * 4 / 5 + 3, screenH / 2 + 3, "3.", Color::Magenta);
    drawText(screenW * 4 / 5 + 3, screenH * 3 / 4, "STR:", Color::Magenta);
    drawText(screenW * 4 / 5 + 3, screenH * 3 / 4 + 1, "CON:", Color::Magenta);
    drawText(screenW * 4 / 5 + 3, screenH * 3 / 4 + 2, "INT:", Color::Magenta);

    drawText(2, screenH - 2, "Level:", Color::Magenta);
    drawText(screenW / 5, screenH - 2, "HP:", Color::Magenta);
    drawText(screenW * 2 / 5, screenH - 2, "MP:", Color::Magenta);
    drawText(screenW * 3 / 5, screenH - 2, "XP:", Color::Magenta);
    drawText(screenW * 4 / 5 + 3, screenH - 2, "(P): Pause", Color::Magenta);
  }

  void Game::drawMinimap() {
    using namespace Renderer;

    // Center of minimap
    int mapCenterX = screenW * 9 / 10;
    int mapCenterY = screenH / 8;

    for (int dy = 1 - screenH / 8; dy <= screenH / 8 - 1; dy++) {
      for (int dx = 3 - screenW / 10; dx <= screenW / 10 - 3; dx++) {
        int worldX = playerX + dx;
        int worldY = playerY + dy;

        if (worldX == playerX && worldY == playerY) {
          drawPlayer(mapCenterX, mapCenterY);
        } else if (map.isExplored(worldX, worldY)) {
          World::TileType tile = map.getTile(worldX, worldY);
          if (tile == World::TileType::Wall) {
            renderer.drawCell(mapCenterX + dx, mapCenterY + dy, "▓", Color::White);
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
 
        if (map.isExplored(x, y)) {
          if (tile == World::TileType::Wall) {
            renderer.drawCell(x + mapX, y + mapY, "▓", Color::White);
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
    drawText(screenW * 2 / 5 - 3, screenH / 4 + 1, "PAUSED", Color::Red, Style::Bold);
    drawText(2, screenH / 4 + 2, "P: Resume", Color::Cyan, Style::Underline);
    drawText(2, screenH / 4 + 3, "Q: Quit", Color::Cyan, Style::Underline);
    drawText(2, screenH / 4 + 4, "M: View Full Map", Color::Cyan, Style::Underline);
  }

  /*
  void Game::clearViewport() {
    for (int y = screenH / 4 + 1; y < screenH - 3; y++) {
      for (int x = 1; x < screenW * 4 / 5; x++) {
        renderer.drawCell(x, y, " ");
      }
    }
  }
  */

constexpr std::string_view FrontFar[] = {"|###########################################################################|",
                                         "|###########################################################################|",
                                         "|###########################################################################|",
                                         "|###########################################################################|",
                                         "|###########################################################################|",
                                         "|###########################################################################|",
                                         "|###########################################################################|",
                                         "|###########################################################################|"};

constexpr std::string_view FrontMid[] = {"|###############################################################################|",
                                         "|###############################################################################|",
                                         "|###############################################################################|",
                                         "|###############################################################################|",
                                         "|###############################################################################|",
                                         "|###############################################################################|",
                                         "|###############################################################################|",
                                         "|###############################################################################|",
                                         "|###############################################################################|",
                                         "|###############################################################################|",
                                         "|###############################################################################|",
                                         "|###############################################################################|"};

constexpr std::string_view FrontNear[] = {"|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|",
                                         "|#####################################################################################|"};

constexpr std::string_view LeftFar[] = {"####|\\",
                                        "####||",
                                        "####||",
                                        "####||",
                                        "####||",
                                        "####||",
                                        "####||",
                                        "####|/"};

constexpr std::string_view LeftMid[] = {"####|\\",
                                        "####||\\",
                                        "####|||",
                                        "####|||",
                                        "####|||",
                                        "####|||",
                                        "####|||",
                                        "####|||",
                                        "####|||",
                                        "####|||",
                                        "####||/",
                                        "####|/"};

constexpr std::string_view LeftNear[] = {"####|\\",
                                        "####||\\",
                                        "####|||\\",
                                        "####||||",
                                        "####||||",
                                        "####||||",
                                        "####||||",
                                        "####||||",
                                        "####||||",
                                        "####||||",
                                        "####||||",
                                        "####||||",
                                        "####||||",
                                        "####||||",
                                        "####||||",
                                        "####|||/",
                                        "####||/",
                                        "####|/"};

constexpr std::string_view LeftNext[] = {"|\\",
                                        "||\\",
                                        "|||\\",
                                        "||||\\",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "||||/",
                                        "|||/",
                                        "||/",
                                        "|/"};

constexpr std::string_view RightFar[] = {"/|####",
                                        "||####",
                                        "||####",
                                        "||####",
                                        "||####",
                                        "||####",
                                        "||####",
                                        "\\|####"};

constexpr std::string_view RightMid[] = {" /|####",
                                        "/||####",
                                        "|||####",
                                        "|||####",
                                        "|||####",
                                        "|||####",
                                        "|||####",
                                        "|||####",
                                        "|||####",
                                        "|||####",
                                        "\\||####",
                                        " \\|####"};

constexpr std::string_view RightNear[] = {"  /|####",
                                        " /||####",
                                        "/|||####",
                                        "||||####",
                                        "||||####",
                                        "||||####",
                                        "||||####",
                                        "||||####",
                                        "||||####",
                                        "||||####",
                                        "||||####",
                                        "||||####",
                                        "||||####",
                                        "||||####",
                                        "||||####",
                                        "\\|||####",
                                        " \\||####",
                                        "  \\|####"};

constexpr std::string_view RightNext[] = {"   /|",
                                        "  /||",
                                        " /|||",
                                        "/||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "|||||",
                                        "\\||||",
                                        " \\|||",
                                        "  \\||",
                                        "   \\|"};


  void Game::drawPOV() {
    int cx = screenW * 2 / 5 ;
    int cy = screenH / 2;

    //Front should be drawn last
    const int order[] = {-1, 1, 0};

    for (int d = 3; d >= 0; d--) { //Distance
      for (int s : order) { //Side
        if (d == 0 && s == 0) continue;

        //world_coord = player_coord + forward_vector*direction + right_vector*side
        int worldX = playerX + pdx[playerD] * d + psx[playerD] * s;
        int worldY = playerY + pdy[playerD] * d + psy[playerD] * s;
        /*
        switch (playerD) {
          case North: worldX += s; worldY -= d; break;
          case East: worldX += d; worldY += s; break;
          case South: worldX -= s; worldY += d; break;
          case West: worldX -= d; worldY -= s; break;
        }
        */
        World::TileType tile = map.getTile(worldX, worldY);
        if (tile != World::TileType::Wall) continue;

        if (s == -1) { //Left
          if (d == 3) drawBlock(cx + s * 42, cy, LeftFar);
          if (d == 2) drawBlock(cx + s * 44, cy - 2, LeftMid);
          if (d == 1) drawBlock(cx + s * 47, cy - 5, LeftNear);
          if (d == 0) drawBlock(cx + s * 47, cy - 9, LeftNext);
        } else if (s == 1) { //Right
          if (d == 3) drawBlock(cx + s * 37, cy, RightFar);
          if (d == 2) drawBlock(cx + s * 38, cy - 2, RightMid);
          if (d == 1) drawBlock(cx + s * 40, cy - 5, RightNear);
          if (d == 0) drawBlock(cx + s * 43, cy - 9, RightNext);
        } else if (s == 0) { //Front
          if (d == 3) drawBlock(cx - 38, cy, FrontFar);
          if (d == 2) drawBlock(cx - 40, cy - 2, FrontMid);
          if (d == 1) drawBlock(cx - 43, cy - 5, FrontNear);
        }
      }
    }
  }

  void Game::draw() {
    renderer.clear();

    drawUIBorders();
    drawMinimap();

    if (currState == GameState::Running) {
      drawPOV();
    } else if (currState == GameState::ViewMap) {
      drawFullmap();
    } else if (currState == GameState::PauseMenu) {
      drawPauseMenu();
    }

    renderer.render();
  }
}
