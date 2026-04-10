#include "input.hpp"
#include <unistd.h>
#include <iostream>

namespace RPG::Engine {

  Input::Input() {
    enableRawMode();
  }

  Input::~Input() {
    disableRawMode();
  }

  void Input::enableRawMode() {
    tcgetattr(STDIN_FILENO, &og_termios);
    struct termios raw = og_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    std::cout << "\033[?25l"; //Hide cursor
    std::cout << "\033[2J\033[H"; //Clear screen
    std::cout << std::flush;
  }

  void Input::disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &og_termios);
    std::cout << "\033[?25h"; //Show cursor
    std::cout << "\033[2J\033[H"; //Clear screen
    std::cout << std::flush;
  }

  char Input::getKey() {
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1) {
      return c;
    }
    return '\0';
  }
}
