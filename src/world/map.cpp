#include "map.hpp"

namespace World {
  Map::Map(int w, int h) : width(w), height(h) {
    grid.resize(width * height, TileType::None);
    explored.resize(width * height, false);
  }

  void Map::setTile(int x, int y, TileType type) {
    if (inBounds(x, y)) {
      grid[getIndex(x, y)] = type;
    }
  }

  TileType Map::getTile(int x, int y) const {
    if (inBounds(x, y)) {
      return grid[getIndex(x, y)];
    }
    return TileType::Wall; //Out of bounds = wall
  }

  void Map::clear(TileType type) {
    std::fill(grid.begin(), grid.end(), type);
    std::fill(explored.begin(), explored.end(), false);
  }

  bool Map::isExplored(int x, int y) const {
    if (inBounds(x, y)) {
      return explored[getIndex(x, y)];
    }
    return false;
  }

  void Map::setExplored(int x, int y, bool state) {
    if (inBounds(x, y)) {
      explored[getIndex(x, y)] = state;
    }
  }
}
