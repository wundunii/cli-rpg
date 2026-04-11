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
  public:
    Map(int w, int h);

    inline int getIndex(int x, int y) const {
      return (y * width) + x;
    }

    inline bool inBounds(int x, int y) const {
      return x >= 0 && x < width && y >= 0 && y < height;
    }

    void setTile(int x, int y, TileType type);
    TileType getTile(int x, int y) const;

    int getWidth() const {return width;}
    int getHeight() const {return height;}

    void fill(TileType type = TileType::None);
  };
}
