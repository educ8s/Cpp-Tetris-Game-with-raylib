#include "block.h"
#include "colors.h"
#include "raylib.h"
#include "position.h"
#include <vector>

Block::Block()
{
    rotationState = 0;
    cellSize = 30;
    row_offset = 0;
    column_offset = 0;
    colors = GetCellColors();
}

void Block::Draw(int offsetX, int offsetY)
{
    vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int columns)
{
    row_offset += rows;
    column_offset += columns;
}

void Block::Rotate()
{
    rotationState++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::UndoRotation()
{
    rotationState--;
    if (rotationState == -1)
    {
        rotationState = (int)cells.size() - 1;
    }
}

vector<Position> Block::GetCellPositions()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position position = Position(item.row + row_offset, item.column + column_offset);
        movedTiles.push_back(position);
    }
    return movedTiles;
}