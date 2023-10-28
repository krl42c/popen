#include <iostream>
#include <vector>
#include "raylib.h"
#include "popen.h"

int main() {
    po::Pool p = po::create_pool(".", true);
    po::load_pool(&p);

    const auto first_element = p.images.at(0);

    const int screen_width = first_element.width;
    const int screen_heigth = first_element.height;

    InitWindow(screen_width, screen_heigth, "popen");

    size_t start = 0;
    size_t end = p.images.size();
    size_t curr = 0;

    auto textures = po::tex_array(&p, start, end);

    SetTargetFPS(60);               
    while (!WindowShouldClose())   
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(textures.at(curr), 0,0,WHITE);
        EndDrawing();
    }

    po::unload_pool(&p);
    CloseWindow();        
    return 0;
}
