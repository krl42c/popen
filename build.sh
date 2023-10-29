clang++ \
    src/popen.cc src/main.cc \
    -L/opt/homebrew/Cellar/raylib/4.5.0/lib -I/opt/homebrew/Cellar/raylib/4.5.0/include -lraylib -D_RAYLIB_BACKEND \
    -std=c++20 \
    -o popen\
    -Wall -Wextra -Wpedantic\
