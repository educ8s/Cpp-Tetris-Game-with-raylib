#pragma once

#include <map>
#include "position.h"
#include <vector>
#include <raylib.h>

using namespace std;
class Block
{
public:
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    void Rotate();
    void UndoRotation();
    vector<Position> GetCellPositions();
    int id;
    int row_offset;
    int column_offset;
    map<int, vector<Position>> cells;

private:
    vector<Color> colors;
    int rotationState;
    int cellSize;
};