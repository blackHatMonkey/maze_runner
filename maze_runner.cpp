#include <algorithm>
#include <vector>

#include "maze.hpp"
#include "wall.hpp"

bool runMaze(Maze &maze, std::vector<int> &path, int currentCell, int endCell);


/**
 * @brief Find the path from startCell to endCell if it exists.
 * 
 * @param theMaze A maze.
 * @param path Path to the endCell.
 * @param startCell The starting cell(position).
 * @param endCell The position of the end goal.
 * @return int The length of the path.
 */
int runMaze(Maze &theMaze, int path[], int startCell, int endCell) {
  std::vector<int> possiblePath;
  runMaze(theMaze, possiblePath, startCell, endCell);

  std::copy(possiblePath.begin(), possiblePath.end(), path);

  return possiblePath.size();
}

/**
 * @brief Find the path from currentCell to endCell if it exists.
 * 
 * @param maze A maze.
 * @param path Path to the endCell.
 * @param currentCell The current cell we are on.
 * @param endCell The position of the end goal.
 * @return true If we have found the end goal.
 * @return false If we have reached a dead end.
 */
bool runMaze(Maze &maze, std::vector<int> &path, int currentCell, int endCell) {
  maze.mark(currentCell);
  path.push_back(currentCell);

  if (currentCell == endCell) {
    return true;
  }

  auto row = maze.getRow(currentCell);
  auto column = maze.getCol(currentCell);
  auto totalRows = maze.numRows();
  auto totalColumns = maze.numCols();

  auto found = false;

  {
    auto newColumn = column + 1;
    auto rightCell = maze.getCell(row, newColumn);
    if (newColumn < totalColumns && maze.canGo(currentCell, rightCell) &&
        !maze.isMarked(rightCell)) {
      found = runMaze(maze, path, rightCell, endCell);
    }
  }

  {
    auto newRow = row + 1;
    auto downCell = maze.getCell(newRow, column);
    if (!found && newRow < totalRows && maze.canGo(currentCell, downCell) &&
        !maze.isMarked(downCell)) {
      found = runMaze(maze, path, downCell, endCell);
    }
  }

  {
    auto newColumn = column - 1;
    auto leftCell = maze.getCell(row, newColumn);
    if (!found && newColumn >= 0 && maze.canGo(currentCell, leftCell) &&
        !maze.isMarked(leftCell)) {
      found = runMaze(maze, path, leftCell, endCell);
    }
  }

  {
    auto newRow = row - 1;
    auto upCell = maze.getCell(newRow, column);
    if (!found && newRow >= 0 && maze.canGo(currentCell, upCell) &&
        !maze.isMarked(upCell)) {
      found = runMaze(maze, path, upCell, endCell);
    }
  }

  if (!found) {
    path.pop_back();
  }

  return found;
}