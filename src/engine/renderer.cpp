#include "renderer.hpp"
#include <iostream>

namespace Renderer {

  Terminal::Terminal(int w, int h) : width(w), height(h) {
    int totalSize = width * height;
    prevFrame.resize(totalSize);
    currFrame.resize(totalSize);
  }

  void Terminal::clear() {
    std::fill(currFrame.begin(), currFrame.end(), Cell{" ", Color::Default});
  }

  void Terminal::drawCell(int x, int y, const char* c, Color color, Style style) {
    if (inBounds(x, y)) {
      currFrame[getIndex(x, y)] = Cell{c, color, style};
    }
  }

  const char* Terminal::getColor(Color color) {
    switch (color) {
      default: return "\033[39m";
      case Color::Red: return "\033[31m";
      case Color::Green: return "\033[32m";
      case Color::Yellow: return "\033[33m";
      case Color::Blue: return "\033[34m";
      case Color::Magenta: return "\033[35m";
      case Color::Cyan: return "\033[36m";
      case Color::White: return "\033[37m";
      case Color::Black: return "\033[30m";
      case Color::Gray: return "\033[90m";
    }
  }

  const char* Terminal::getStyle(Style style) {
    switch(style) {
      default: return "";
      case Style::Bold: return "\033[1m";
      case Style::Dim: return "\033[2m";
      case Style::Italic: return "\033[3m";
      case Style::Underline: return "\033[4m";
      case Style::Blink: return "\033[5m";
      case Style::Reverse: return "\033[7m";
    }
  }
  void Terminal::render() {
    std::string outBuffer;

    outBuffer.reserve(width * height * 15);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        int i = getIndex(x, y);

        if (currFrame[i] != prevFrame[i]) {
          outBuffer += "\033[" + std::to_string(y + 1) + ";" + std::to_string(x + 1) +  "H"; //Move the cursor
         
          //Hard Reset to prevent bold/blink bleeding 
          outBuffer += "\033[0m";

          if (currFrame[i].style != Style::None) {
            outBuffer += getStyle(currFrame[i].style); //Set Style
          }

          outBuffer += getColor(currFrame[i].color); //Set the color
          outBuffer += currFrame[i].glyph; //Add character

          prevFrame[i] = currFrame[i];
        }
      }
    }

    outBuffer += "\033[0m"; //Reset colors
    std::cout << outBuffer << std::flush; //print the whole buffer
  }
}
