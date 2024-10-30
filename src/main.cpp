#include <vector>
#include <cstdlib>
#include <ctime>

#include "raylib.h"


int main() {
    const int W = 1280;
    const int H = 720;

    const int GW = 18;
    const int GH = 12;

    const int OFFX = W / 2 - (GW * 64 / 2);
    const int OFFY = H / 2 - (GH * 48 / 2) - 16;

    InitWindow(W, H, "The Ballad of Bellum Style Grass");
    SetTargetFPS(60);

    Shader shader = LoadShader(0, "res/waving.fsh");

    std::vector<Texture2D> grasses = {
        LoadTexture("res/grass.png"), LoadTexture("res/short_grass.png")
    };

    int timeLoc = GetShaderLocation(shader, "time");
    int positionLoc = GetShaderLocation(shader, "pos");

    std::srand(std::time(nullptr));
    std::vector<std::pair<Vector2, bool>> positions;

    for (int x = 0; x < GW; x++)
        for (int y = 0; y < GH; y++)
            if (std::rand() % 6)
                positions.push_back(
                    std::pair{
                        Vector2 { (float)x, (float)y },
                        std::rand() % 4 == 0
                    }
                );

    while (!WindowShouldClose()) {
        float time = GetTime();
        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

        BeginDrawing();
            ClearBackground(Color{98, 167, 46, 255});

            for (auto& pos : positions) {
                SetShaderValue(shader, positionLoc, &pos, SHADER_UNIFORM_VEC2);

                BeginShaderMode(shader);
                    Vector2 position = {OFFX + pos.first.x * 64.0f, OFFY + pos.first.y * 48.0f};
                    DrawTextureEx(grasses[pos.second], position, 0.0, 4.0, WHITE);
                EndShaderMode();
            }

            DrawFPS(20, 20);
        EndDrawing();
    }

    UnloadShader(shader);
    for (const auto& tex : grasses)
        UnloadTexture(tex);
    CloseWindow();

    return 0;
}
