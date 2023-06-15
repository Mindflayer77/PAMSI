cmake_minimum_required(VERSION 3.25.2)
project(Game)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(Game inc/Game.h inc/TextureManager.h src/Game.cpp src/TextureManager.cpp src/main.cpp)
target_link_libraries(Game "/usr/local/lib/libSDL2_image-2.0.so.0"
"/usr/local/lib/libSDL2_image-2.0.so.0.600.2"
"/usr/local/lib/libSDL2_image-2.0.so.0.600.3"
"/usr/local/lib/libSDL2_image.a"
"/usr/local/lib/libSDL2_image.so"
"/usr/local/lib/libSDL2-2.0.so.0"
"/usr/local/lib/libSDL2-2.0.so.0.2600.5"
"/usr/local/lib/libSDL2.a"
"/usr/local/lib/libSDL2main.a"
"/usr/local/lib/libSDL2.so"
"/usr/local/lib/libSDL2_test.a"
)
target_compile_options(Game PRIVATE -lSDL2_image -lSDL2_image<pre>)