cmake_minimum_required(VERSION 3.10)

project(hungarian)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-std=c++17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB SRC
     "./*.cpp"
)

# Add your source files and set up the build
add_executable(hung main.cpp ${SRC})
