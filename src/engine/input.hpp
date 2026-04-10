#pragma once
#include <termios.h>

namespace RPG::Engine {
  class Input {
  private:
    struct termios og_termios;
    void enableRawMode();
    void disableRawMode();

  public:
    Input();
    ~Input();

    char getKey();
  };
}
