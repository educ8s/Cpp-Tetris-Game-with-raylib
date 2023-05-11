#pragma once

#include <raylib.h>
#include <vector>

using namespace std;

class Grid
{
public:
    Grid();
    bool IsInside(int row, int column);
    int grid[20][10];
    void PrintGrid();
    void Draw();
    bool IsEmpty(int row, int column);
    void Reset();
    int ClearFullRows();

private:
    int numRows;
    int numCols;
    int cellSize;
    vector<Color> colors;
    void initialize();
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int number);
};