#pragma once
#include <random>
#include "map.hpp"

namespace World {
  struct Point {int x, y;};

  class Generator {
  private:
    std::mt19937 rng;

    bool canPlace(const Map& map, int x, int y);
  public:
    Generator();

    int randomInt(int min, int max);
    void genDungeon(Map& map);
  };
}
