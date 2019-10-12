#include "wall.h"

void generateAllWalls(int, int, Wall[]);

int generateMaze(int row, int col, Wall walls[]) {
  generateAllWalls(row, col, walls);

  return (row - 1) * col + (col - 1) * row;
}

void generateAllWalls(int row, int col, Wall walls[]) {
  auto lastRow = row - 1;
  auto lastCol = col - 1;
  auto wallNumber = 0;

  for (auto i = 0; i < row; i++) {
    for (auto j = 0; j < col; j++) {
      auto currentCell = (i * (row + 1)) + j;
      if (j != lastCol) {
        walls[wallNumber].set(currentCell, currentCell + 1);
        wallNumber++;
      }

      if (i != lastRow) {
        auto bottomCell = currentCell + col + 1;
        walls[wallNumber].set(currentCell, bottomCell);
        wallNumber++;
      }
    }
  }
}


int main(){
  Wall walls[50];
  generateMaze(3, 4, walls);

  return 0;
}