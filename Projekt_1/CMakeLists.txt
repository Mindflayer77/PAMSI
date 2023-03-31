cmake_minimum_required(VERSION 3.26.0)
project(App)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
add_executable(App src/App.cpp)
target_link_libraries(App ${wxWidgets_LIBRARIES})

