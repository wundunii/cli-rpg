#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cstdint>

namespace Renderer {

  enum class Color : uint8_t {
    Default,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Black,
    Gray
  };

  enum class Style : uint8_t {
    None,
    Bold,
    Dim,
    Italic,
    Underline,
    Blink,
    Reverse
  };

  struct Cell {
    std::string glyph = " ";
    Color color = Color::Default;
    Style style = Style::None;

    //Only needed for cells' tails cleaning
    //int length = std::string_view(glyph).length();

    bool operator==(const Cell& other) const {
      return std::string_view(glyph) == std::string_view(other.glyph) && color == other.color && style == other.style;
    }

    bool operator!=(const Cell& other) const {
      return !(*this == other);
    }
  };

  class Terminal {
  public:
    //Using the size of classic terminals for now
    Terminal(int w, int h);

    int getWidth() const {return width;}
    int getHeight() const {return height;}

    void clear();
    void drawCell(int x, int y, std::string c, Color color = Color::Default, Style style = Style::None);
    void render();
  private:
    int width;
    int height;

    std::vector<Cell> prevFrame;
    std::vector<Cell> currFrame;

    const char* getColor(Color color);
    const char* getStyle(Style style);

    int getIndex(int x, int y) const {
      return (y * width) + x;
    }

    bool inBounds(int x, int y) const {
      return x >= 0 && x < width && y >= 0 && y < height;
    }
  };
}
