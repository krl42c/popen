#include "popen.h"

// Image/Texture pool related functions
bool po::load_pool(Pool *p) {
    assert(p != nullptr); 
    assert(!p->files.empty());

    for (auto str : p->files) {
        if (!str.empty()) {
            auto image = LoadImage(str.c_str());
            if (IsImageReady(image)) {
                p->images.push_back(image);
#ifdef DEBUG
                printf("File [%s] loaded correctly into main pool", str.c_str());
#endif
            } else {
#ifdef DEBUG
            printf("Failed to load [%s], file not ready", str.c_str());
#endif
            }
        }
    }
    return !p->images.empty();
}

bool po::unload_pool(Pool *p) {
    assert(p != nullptr); 
    for (auto& image : p->images) {
        UnloadImage(image);
    }
    return p->images.empty();
}

po::Pool po::create_pool(const char* directory, bool recursive) {
    assert(dir_exists(directory)); 

    Pool p{};

    if (recursive) po::fill_with_images(std::filesystem::recursive_directory_iterator(directory), &p.files);
    if (!recursive) po::fill_with_images(std::filesystem::directory_iterator(directory), &p.files);

    assert(!p.files.empty());

    return p;
}

std::vector<Texture2D> po::tex_array(Pool *p, size_t from, size_t to) {    
    std::vector<Texture2D> texture_vec;
         
    std::ranges::for_each(std::views::iota(from, to), [&texture_vec, p](size_t i) {
        texture_vec.push_back(LoadTextureFromImage(p->images.at(i)));
    });
    return texture_vec;
}

template<typename Iterator>
void po::fill_with_images(Iterator it, std::vector<std::string> *target) {
    std::ranges::for_each(it, [&target](const auto& dir_entry) {
        auto ext = dir_entry.path().extension();
        if (ext == ".png" || ext == ".PNG" || ext == ".jpg" || ext == ".JPG") {
            if(dir_entry.is_regular_file()) {
                target->push_back(dir_entry.path());
            }
        }
    });
}


// Utility

bool dir_exists(const char* dir) { 
    std::ifstream test(dir);
    return test ? true : false;
}


