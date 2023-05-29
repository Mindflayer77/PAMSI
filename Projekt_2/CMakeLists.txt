cmake_minimum_required(VERSION 3.26.3)
project(Sorting)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(Sorting inc/Graphics.h inc/Visualization.h inc/Sorting.h inc/Movie.h inc/ReadData.h src/Sorting.cpp 
src/Graphics.cpp src/Visualization.cpp src/ReadData.cpp src/main.cpp inc/Game.h src/Game.cpp 
inc/TextureManager.h src/TextureManager.cpp inc/Performance.h src/Performance.cpp)
# target_link_libraries(Sorting ${SDL2_LIBRARIES})
target_link_libraries(Sorting "/usr/local/lib/libSDL2_image-2.0.so.0"
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
target_compile_options(Sorting PRIVATE -lSDL2_image -lSDL2_image<pre>)