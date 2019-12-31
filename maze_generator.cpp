#include <algorithm>
#include <random>
#include <set>
#include <vector>

#include "disjointset.hpp"
#include "wall.hpp"

void generateAllWalls(int, int, std::vector<Wall> &);
void removeRandomWalls(int, int, std::vector<Wall> &);
bool shouldRemoveWall(const Wall &);
void copyAllWalls(std::vector<Wall>, Wall[]);

constexpr auto emptyCell = -1;

/**
 * @brief Generate a random maze.
 *
 * @param row Width of the maze.
 * @param col Height of the maze.
 * @param walls All walls in maze.
 * @return int Number of generated walls.
 */
int generateMaze(int row, int col, Wall walls[]) {
  const auto maximumNumberOfWalls = (row - 1) * col + (col - 1) * row;
  std::vector<Wall> possibleWalls(maximumNumberOfWalls);

  generateAllWalls(row, col, possibleWalls);
  removeRandomWalls(row, col, possibleWalls);
  copyAllWalls(possibleWalls, walls);

  return possibleWalls.size();
}

/**
 * @brief Generate all possible walls in the maze.
 *
 * @param row Width of the maze.
 * @param col Height of the maze.
 * @param walls All walls in maze.
 */
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

/**
 * @brief Remove random walls in the maze until all cells are connected.
 *
 * This function guarantees that all cells in the maze are accessable.
 *
 * @param row Width of the maze.
 * @param col Height of the maze.
 * @param walls All walls in maze.
 */
void removeRandomWalls(int row, int col, std::vector<Wall> &walls) {
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

/**
 * @brief Returns whether a wall should be removed or not.
 *
 * @param wall A wall.
 * @return true If wall should be removed.
 * @return false If wall should be kept.
 */
bool shouldRemoveWall(const Wall &wall) { return wall.cell1() == emptyCell; }

/**
 * @brief Copies all the walls from source to destination.
 *
 * @param source Source of copy.
 * @param destination Destination of copy.
 */
void copyAllWalls(std::vector<Wall> source, Wall destination[]) {
  std::copy(source.begin(), source.end(), destination);
}