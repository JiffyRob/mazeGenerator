#include <map>
#include <array>
#include <deque>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using Coord = std::array<int, 2>;

enum DIRECTION {NORTH=1, SOUTH=2, EAST=4, WEST=8};
std::array<DIRECTION, 4> directions = {NORTH, EAST, SOUTH, WEST};

std::map<DIRECTION, int> DX = {{EAST, 1}, {WEST, -1}, {NORTH, 0}, {SOUTH, 0}};
std::map<DIRECTION, int> DY = {{EAST, 0}, {WEST, 0}, {NORTH, -1}, {SOUTH, 1}};
std::map<DIRECTION, DIRECTION> REVERSE = {{EAST, WEST}, {WEST, EAST}, {NORTH, SOUTH}, {SOUTH, NORTH}};

class Maze {
    public:
      int getWidth() {
        return width;
      }
      int getHeight() {
        return height;
      }
      int getAt(int x, int y) {
        return nodes[y][x];
      }
      int getAt(Coord coord) {
        return nodes[coord[1]][coord[0]];
      }
      int getCurrentX() {
        return currentX;
      }
      int getCurrentY() {
        return currentY;
      }

      void prep(int width, int height) {
        // initialize vars
        this->width = width;
        this->height = height;
        this->currentX = -1;
        this->currentY = -1;
        if (nodes.size()) {
          nodes.clear();
        }
        if (cells.size()) {
          cells.clear();
        }
        // fill grid
        for (int row = 0; row < height; row++) {
          nodes.push_back(std::vector<int>());
          for (int col = 0; col < width; col++) {
            nodes.back().push_back(0);
          }
        }
        // add beginning cell
        Coord start = {rand() % width, rand() % height};
        cells.push_front(start);
      }

      bool generate() {
        if (cells.size() > 0) {
          bool carved = false;
          currentX = cells.front()[0];
          currentY = cells.front()[1];
          std::random_shuffle(directions.begin(), directions.end());
          for (int i = 0; i < 4; i++) {
            DIRECTION dir = directions[i];
            int nx = currentX + DX[dir];
            int ny = currentY + DY[dir];
            if (nx >= 0 && ny >= 0 && nx < width && ny < height && nodes[ny][nx] == 0) {
               nodes[currentY][currentX] |= dir;
               nodes[ny][nx] |= REVERSE[dir];
               Coord coord = {nx, ny};
               cells.push_front(coord);
               carved = true;
               break;
            }
          }
          if (!carved) {
            cells.pop_front();
          }
          currentX = cells.front()[0];
          currentY = cells.front()[1];
          return false;
        }
        return true;
      }

    void close() {
      nodes.clear();
      cells.clear();
    }

    private:
      std::deque<Coord> cells;
      std::vector<std::vector<int>> nodes;
      int currentX;
      int currentY;
      int width;
      int height;
};