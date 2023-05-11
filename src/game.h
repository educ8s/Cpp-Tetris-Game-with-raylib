#pragma once

#include "grid.h"
#include <vector>
#include "blocks.cpp"

class Game
{
public:
    Game();
    ~Game();

    void Draw();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    void RotateBlock();
    void HandleInput();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);

    Music music;
    bool gameOver;
    int score;

private:
    void LockBlock();
    vector<Block> GetAllBlocks();
    Block GetRandomBlock();
    bool BlockFits();
    bool BlockInside();
    void LoadMusic();
    Sound rotateSound;
    Sound clearSound;
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Grid grid;
};