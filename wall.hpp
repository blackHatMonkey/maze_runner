#ifndef WALL_HPP
#define WALL_HPP

class Wall {
  int cells[2]{-1};

public:
  Wall(int c1, int c2) {
    cells[0] = c1;
    cells[1] = c2;
  }
  
  Wall() = default;

  void set(int c1, int c2) {
    cells[0] = c1;
    cells[1] = c2;
  }
  int cell1() const noexcept { return cells[0]; }
  int cell2() const noexcept { return cells[1]; }
};

#endif