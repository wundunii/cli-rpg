#include "renderer.hpp"
#include <iostream>

namespace Renderer {

  Terminal::Terminal(int w, int h) : width(w), height(h) {
    int totalSize = width * height;
    prevFrame.resize(totalSize);
    currFrame.resize(totalSize);
  }

  void Terminal::clear() {
    std::fill(currFrame.begin(), currFrame.end(), Cell{" ", Color::Default, Style::None});
  }

  void Terminal::drawCell(int x, int y, const char* c, Color color, Style style) {
    if (inBounds(x, y)) {
      currFrame[getIndex(x, y)] = Cell{c, color, style};
    }
  }

  const char* Terminal::getColor(Color color) {
    switch (color) {
      default: return "39m";
      case Color::Red: return "31m";
      case Color::Green: return "32m";
      case Color::Yellow: return "33m";
      case Color::Blue: return "34m";
      case Color::Magenta: return "35m";
      case Color::Cyan: return "36m";
      case Color::White: return "37m";
      case Color::Black: return "30m";
      case Color::Gray: return "90m";
    }
  }

  const char* Terminal::getStyle(Style style) {
    switch(style) {
      default: return "0;";
      case Style::None: return "0;";
      case Style::Bold: return "1;";
      case Style::Dim: return "2;";
      case Style::Italic: return "3;";
      case Style::Underline: return "4;";
      case Style::Blink: return "5;";
      case Style::Reverse: return "7;";
    }
  }
  void Terminal::render() {
    std::string outBuffer;

    //Reserve some memory for the buffer, might change later?
    outBuffer.reserve(width * height * 15);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        int i = getIndex(x, y);

        //Syntax: \033[<STYLE>;<FG_COLOR>;<BG_COLOR>m
        if (currFrame[i] != prevFrame[i]) {
          outBuffer += "\033[" + std::to_string(y + 1) + ";" + std::to_string(x + 1) +  "H"; //Move the cursor

          //Reset style and color
          outBuffer += "\033[0m";

          //Start of ASCII escape sequence
          outBuffer += "\033[";

          if (currFrame[i].style != Style::None) {
            outBuffer += getStyle(currFrame[i].style); //Set Style
          }

          outBuffer += getColor(currFrame[i].color); //Set the color
          outBuffer += currFrame[i].glyph; //Add character

          prevFrame[i] = currFrame[i];
        }
      }
    }

    //outBuffer += "\033[0m"; //not sure if needed.
    std::cout << outBuffer << std::flush; //print the whole buffer
  }
}
