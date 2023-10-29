#include <stdint.h>
#include <cassert>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm> 
#include <ranges>
#include <memory>
#include <stdexcept> 

#ifdef _RAYLIB_BACKEND
    #include "raylib.h"
#endif 

#ifdef _SDL2_BACKEND
    #include <SDL2.h>
#endif 

#pragma once

namespace po {
    struct Pool {
        std::vector<std::string> files;
        std::vector<Image> images;
    };
    
    bool load_pool(Pool *p);
    bool unload_pool(Pool *p);
    
    std::shared_ptr<Pool> create_pool(const char* directoy, bool recursive);
    Pool create_pool(std::vector<const char*> files);
    Pool create_pool();

    std::vector<Texture2D> tex_array(std::shared_ptr<Pool> p, size_t from, size_t to);

    template<typename Iterator>
    void fill_with_images(Iterator it, std::vector<std::string> *target);

    template<class Wrapper, class Result> 
    struct View_Manager {
        std::optional<std::shared_ptr<Pool>> image_pool;
        std::vector<Result> result_vector;

        Wrapper wrap;

        void load_single(const char* file);
        void load_directory(const char* dir);

        View_Manager(const char* path, bool recursive = false) {
            const std::filesystem::path fs_path(path);
            if (std::filesystem::is_directory(fs_path)) {
                this->image_pool = create_pool(path, recursive);
                std::ranges::for_each(this->image_pool->get()->files, [this](const auto& file) {
                        this->result_vector.push_back(this->wrap.load_image(file));
                });
            }
        }
    };

#ifdef _RAYLIB_BACKEND
    struct Raylib_Wrapper {
        Texture2D load_image(std::string file) {
            const auto image = LoadImage(file.c_str());
            if (!IsImageReady(image)) throw std::runtime_error("raylib failed at LoadImage");
            
            return LoadTextureFromImage(image);
        }

        Raylib_Wrapper() {};
        ~Raylib_Wrapper() {};
    };
#endif 

#ifdef _SDL2_BACKEND
    struct SDL2_Wrapper {
        SDL_Renderer renderer; 

        SDL_Texture *load_image(std::string file) {
            return IMG_LoadTexture(this->renderer&, file.c_str());     
        }
    };
#endif

}


// Utility
bool dir_exists(const char* dir);
