#pragma once
#include <string>
#include <iostream>
#include <vector>

namespace Renderer {

  enum class Color {
    Reset = 0,
    Default = 39,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
    Black = 30,
    Gray = 90
  };

  enum class Style {
    None = 0,
    Bold = 1,
    Dim = 2,
    Italic = 3,
    Underline = 4,
    Blink =5,
    Reverse = 7
  };

  struct Cell {
    const char* glyph = " ";
    Color color = Color::Default;
    Style style = Style::None;

    bool operator!=(const Cell& other) const {
      return glyph != other.glyph || color != other.color || style != other.style;
    }
  };

  class Terminal {
  public:
    Terminal(int w = 80, int h = 24);

    void clear();
    void drawCell(int x, int y, const char* c, Color color = Color::Default, Style style = Style::None);
    void render();

  private:
    int width;
    int height;

    std::vector<Cell> prevFrame;
    std::vector<Cell> currFrame;

    const char* getColor(Color color);
    const char* getStyle(Style style);

    inline int getIndex(int x, int y) const {
      return (y * width) + x;
    }

    inline bool inBounds(int x, int y) const {
      return x >= 0 && x < width && y >= 0 && y < height;
    }
  };
}
