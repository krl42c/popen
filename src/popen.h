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
#include "raylib.h"

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
}


// Utility
bool dir_exists(const char* dir);
