#pragma once
#include <random>
#include "map.hpp"

namespace World {
  struct Point {int x, y;};

  class Generator {
  private:
    std::mt19937 rng;

    int randomInt(int min, int max);
    bool canPlace(const Map& map, int x, int y);
  public:
    Generator();

    void genDungeon(Map& map);
  };
}
