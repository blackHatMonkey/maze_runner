#include <algorithm>
#include <random>
#include <set>
#include <vector>

#include "disjointset.h"
#include "wall.h"

void generateAllWalls(int, int, std::vector<Wall> &);
void generateRandomMaze(int, int, std::vector<Wall> &);
bool shouldRemoveWall(const Wall &);
void copyAllWalls(std::vector<Wall>, Wall[]);

constexpr auto emptyCell = -1;

int generateMaze(int row, int col, Wall walls[]) {
  const auto maximumNumberOfWalls = (row - 1) * col + (col - 1) * row;
  std::vector<Wall> possibleWalls(maximumNumberOfWalls);

  generateAllWalls(row, col, possibleWalls);
  generateRandomMaze(row, col, possibleWalls);
  copyAllWalls(possibleWalls, walls);

  return possibleWalls.size();
}

void generateAllWalls(int row, int col, std::vector<Wall> &walls) {
  auto lastRow = row - 1;
  auto lastCol = col - 1;
  auto wallNumber = 0;

  for (auto i = 0; i < row; i++) {
    for (auto j = 0; j < col; j++) {
      auto currentCell = (i * col) + j;
      if (j != lastCol) {
        walls[wallNumber].set(currentCell, currentCell + 1);
        wallNumber++;
      }

      if (i != lastRow) {
        auto bottomCell = currentCell + col;
        walls[wallNumber].set(currentCell, bottomCell);
        wallNumber++;
      }
    }
  }
}

void generateRandomMaze(int row, int col, std::vector<Wall> &walls) {
  const auto numberOfCells = row * col;
  auto disjointSet = DisjointSet(numberOfCells);

  for (auto i = 0; i < numberOfCells; i++) {
    disjointSet.makeSet(i);
  }

  auto randomWallIndexes = std::vector<int>(walls.size());
  std::iota(randomWallIndexes.begin(), randomWallIndexes.end(), 0);
  std::shuffle(randomWallIndexes.begin(), randomWallIndexes.end(),
               std::mt19937{std::random_device{}()});

  for (auto &index : randomWallIndexes) {
    auto currentWall = walls[index];

    auto firstCell = currentWall.cell1();
    auto secondCell = currentWall.cell2();

    auto firstRepresentative = disjointSet.findSet(firstCell);
    auto secondRepresentative = disjointSet.findSet(secondCell);

    if (firstRepresentative != secondRepresentative) {
      disjointSet.unionSets(firstRepresentative, secondRepresentative);
      walls[index].set(emptyCell, emptyCell);
    }
  }

  walls.erase(std::remove_if(walls.begin(), walls.end(), shouldRemoveWall),
              walls.end());
}

bool shouldRemoveWall(const Wall &wall) { return wall.cell1() == emptyCell; }

void copyAllWalls(std::vector<Wall> generatedWalls, Wall walls[]) {
  std::copy(generatedWalls.begin(), generatedWalls.end(), walls);
}