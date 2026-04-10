#include "renderer.hpp"
#include <iostream>

namespace RPG::Renderer {

  Terminal::Terminal(int w, int h) : width(w), height(h) {
    int totalSize = width * height;
    prevFrame.resize(totalSize);
    currFrame.resize(totalSize);
  }

  void Terminal::clear() {
    std::fill(currFrame.begin(), currFrame.end(), Cell{' ', Color::Default});
  }

  void Terminal::drawChar(int x, int y, char c, Color color) {
    if (inBounds(x, y)) {
      currFrame[getIndex(x, y)] = Cell{c, color};
    }
  }
  // TODO: drawString
  std::string Terminal::getColor(Color color) {
    return "\033[" + std::to_string(static_cast<int>(color)) + "m";
  }

  void Terminal::render() {
    std::string outBuffer;

    outBuffer.reserve(width * height * 15);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        int i = getIndex(x, y);

        if (currFrame[i] != prevFrame[i]) {
          outBuffer += "\033[" + std::to_string(y + 1) + ";" + std::to_string(x + 1) +  "H"; //Move the cursor
          outBuffer += getColor(currFrame[i].color); //Set the color
          // TODO: Incorperate blinking color
          outBuffer += currFrame[i].glyph; //Add character

          prevFrame[i] = currFrame[i];
        }
      }
    }

    outBuffer += "\033[0m"; //Reset colors
    std::cout << outBuffer << std::flush; //print the whole buffer
  }
}
