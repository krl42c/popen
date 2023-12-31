#include <iostream>
#include <vector>
#include <memory>
#include "raylib.h"
#include "popen.h"

int main(int argc, char* argv[]) {
    if (argc == 2) std::cout << "2 argc\n";

    auto p = po::create_pool(".", true);
    po::load_pool(p.get());

    const auto first_element = p->images.at(0);

    const int screen_width = first_element.width;
    const int screen_heigth = first_element.height;

    InitWindow(screen_width, screen_heigth, "popen");

    constexpr std::size_t start = 0;
    ssize_t curr = 0;

    std::size_t end = p->images.size();
    

    po::View_Manager<po::Raylib_Wrapper, Texture2D> manager(".");
    auto textures = manager.result_vector;
    
    SetTargetFPS(60);               
    while (!WindowShouldClose())   
    {
        if (IsKeyReleased(KEY_A)) {
            if ((curr - 1) >= 0) curr -= 1;
        }

        if (IsKeyReleased(KEY_D)) {
            if (textures.size() > (curr + 1)) curr += 1;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(textures.at(curr), 0,0,WHITE);
        EndDrawing();
    }

    //po::unload_pool(p.get());
    CloseWindow();        
    return 0;
}
