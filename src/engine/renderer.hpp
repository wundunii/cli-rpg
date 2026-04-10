#pragma once
#include <string>
#include <iostream>
#include <vector>

namespace RPG::Renderer {

  enum class Color {
    Reset = 0,
    Default = 39,
    Red = 31,
    Green = 32,
    Yellow = 33, // "\033[5;33m" for blinking
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37
  };

  struct Cell {
    char glyph = ' ';
    Color color = Color::Default;

    bool operator!=(const Cell& other) const {
      return glyph != other.glyph || color != other.color;
    }
  };

  class Terminal {
  public:
    Terminal(int w = 80, int h = 24);

    void clear();
    void drawChar(int x, int y, char c, Color color = Color::Default);
    void drawString(int x, int y, std::string str, Color color = Color::Default);
    void render();

  private:
    int width;
    int height;

    std::vector<Cell> prevFrame;
    std::vector<Cell> currFrame;

    std::string getColor(Color color);

    inline int getIndex(int x, int y) const {
      return (y * width) + x;
    }

    inline bool inBounds(int x, int y) const {
      return x >= 0 && x < width && y >= 0 && y < height;
    }
  };
}
