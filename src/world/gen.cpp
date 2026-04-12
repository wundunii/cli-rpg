#include <vector>
#include <algorithm>
#include "gen.hpp"

namespace World {
  Generator::Generator() {
    std::random_device rd;
    rng.seed(rd());
  }

  int Generator::randomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
  }

  bool Generator::canPlace(const Map& map, int x, int y) {
    //Stay within bounds
    if (x <= 0 || x >= map.getWidth() - 1 || y <= 0 || y >= map.getHeight() - 1) {
      return false;
    }
    return map.getTile(x, y) == TileType::Wall;
  }

  void Generator::genDungeon(Map &map) {
    map.clear(TileType::Wall);

    std::vector<Point> directions = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};

    std::vector<Point> stack;
    Point start = {1, 1};
    map.setTile(start.x, start.y, TileType::Floor);
    stack.push_back(start);

    while (!stack.empty()) {
      Point current = stack.back();

      //Shuffle directions
      std::shuffle(directions.begin(), directions.end(), rng);

      bool moved = false;
      for (const auto& dir : directions) {
        int nextX = current.x + dir.x;
        int nextY = current.y + dir.y;

        if (canPlace(map, nextX, nextY)) {
          map.setTile(current.x + dir.x / 2, current.y + dir.y / 2, TileType::Floor);
          map.setTile(nextX, nextY, TileType::Floor);

          stack.push_back({nextX, nextY});
          moved = true;
          break;
        }
      }

      if (!moved) {
        stack.pop_back(); //Dead end, backtrack
      }
    }
  }
}
