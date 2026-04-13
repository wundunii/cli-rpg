#pragma once
#include <vector>
#include <cstdint>

namespace World {
  enum class TileType : uint8_t {
    None = 0,
    Floor = 1,
    Wall = 2
  };

  class Map {
  private:
    int width;
    int height;

    std::vector<TileType> grid;

    std::vector<bool> explored;

  public:
    Map(int w, int h);

    int getIndex(int x, int y) const {
      return (y * width) + x;
    }

    bool inBounds(int x, int y) const {
      return x >= 0 && x < width && y >= 0 && y < height;
    }

    void setTile(int x, int y, TileType type);
    TileType getTile(int x, int y) const;

    int getWidth() const {return width;}
    int getHeight() const {return height;}

    void clear(TileType type = TileType::None);

    bool isExplored(int x, int y) const;
    void setExplored(int x, int y, bool state);
  };
}
