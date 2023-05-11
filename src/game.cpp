#include "game.h"
#include <iostream>
#include "position.h"
#include <vector>
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    LoadMusic();

    rotateSound = LoadSound("Sounds/rotate.ogg");
    clearSound = LoadSound("Sounds/clear.ogg");
}

Game::~Game()
{
    UnloadMusicStream(music);
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();
}

void Game::LoadMusic()
{
    InitAudioDevice(); // Initialize audio device
    music = LoadMusicStream("Sounds/music.ogg");
    PlayMusicStream(music);
}

vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

void Game::MoveBlockLeft()
{
    currentBlock.Move(0, -1);
    if (BlockInside() == false || BlockFits() == false)
    {
        currentBlock.Move(0, 1);
    }
}

void Game::Reset()
{
    grid.Reset();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }
    score += moveDownPoints;
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();

    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }

    switch (keyPressed)
    {
    case KEY_LEFT:
        if (!gameOver)
            MoveBlockLeft();
        break;

    case KEY_RIGHT:
        if (!gameOver)
            MoveBlockRight();
        break;
    case KEY_DOWN:
        if (!gameOver)
        {
            MoveBlockDown();
            UpdateScore(0, 1);
        }
        break;
    case KEY_UP:
        if (!gameOver)
            RotateBlock();
        break;
    }
}

void Game::MoveBlockRight()
{
    currentBlock.Move(0, 1);
    if (BlockInside() == false || BlockFits() == false)
    {
        currentBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown()
{
    currentBlock.Move(1, 0);
    if (BlockInside() == false || BlockFits() == false)
    {
        currentBlock.Move(-1, 0);
        LockBlock();
    }
}

bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

bool Game::BlockInside()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsInside(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();
    int completed = grid.ClearFullRows();
    if (completed > 0)
    {
        UpdateScore(completed, 0);
        PlaySound(clearSound);
    }

    if (!BlockFits())
    {
        gameOver = true;
    }
}

void Game::RotateBlock()
{
    currentBlock.Rotate();
    if (BlockInside() == false || BlockFits() == false)
    {
        currentBlock.UndoRotation();
    }
    else
    {
        PlaySound(rotateSound);
    }
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
    }
}