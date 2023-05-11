#include <iostream>
#include <raylib.h>
#include "colors.h"
#include "game.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Game game = Game();

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 250);

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        BeginDrawing();

        if (EventTriggered(0.2) && game.gameOver == false)
        {
            game.MoveBlockDown();
        }

        game.HandleInput();

        ClearBackground(darkBlue);

        DrawTextEx(font, "Score", {365, 15}, 38, 2, white);
        DrawTextEx(font, "Next", {375, 175}, 38, 2, white);
        DrawRectangleRounded(Rectangle{320, 55, 170, 60}, 0.3, 6, lightBlue);
        DrawRectangleRounded(Rectangle{320, 215, 170, 180}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, white);

        if (game.gameOver)
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, white);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}