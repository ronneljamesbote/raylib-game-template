#include "globals.h"
#include "raylib.h"
#include "resource_dir.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

  InitWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT,
             "Vampire Survivor-Like");

  SetWindowMinSize(Constants::GAME_WIDTH, Constants::GAME_HEIGHT);

  InitAudioDevice();

  SetTargetFPS(60);

  SearchAndSetResourceDir("resources");

  // Render texture initialization, used to hold the rendering result so we can
  // easily resize it
  RenderTexture2D target =
      LoadRenderTexture(Constants::GAME_WIDTH, Constants::GAME_HEIGHT);
  SetTextureFilter(target.texture,
                   TEXTURE_FILTER_BILINEAR); // Texture scale filter to use

  while (!WindowShouldClose()) {
    // Compute required framebuffer scaling
    float scale = MIN((float)GetScreenWidth() / Constants::GAME_WIDTH,
                      (float)GetScreenHeight() / Constants::GAME_HEIGHT);

    BeginTextureMode(target);
    {
      ClearBackground(BLUE);
      DrawTexturePro(
          target.texture,
          (Rectangle){0.0f, 0.0f, (float)target.texture.width,
                      (float)-target.texture.height},
          Rectangle{0, 0, Constants::GAME_WIDTH, Constants::GAME_HEIGHT},
          Vector2{0, 0}, 0, WHITE);
    }
    EndTextureMode();

    BeginDrawing();
    {
      ClearBackground(ColorAlpha(BLACK, 0.25f)); // Clear screen background

      DrawTexturePro(
          target.texture,
          (Rectangle){0.0f, 0.0f, (float)target.texture.width,
                      (float)-target.texture.height},
          (Rectangle){
              (GetScreenWidth() - ((float)Constants::GAME_WIDTH * scale)) *
                  0.5f,
              (GetScreenHeight() - ((float)Constants::GAME_HEIGHT * scale)) *
                  0.5f,
              (float)Constants::GAME_WIDTH * scale,
              (float)Constants::GAME_HEIGHT * scale},
          (Vector2){0, 0}, 0.0f, WHITE);
    }
    EndDrawing();
  }

  UnloadRenderTexture(target);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}
