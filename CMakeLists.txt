cmake_minimum_required(VERSION 3.10)

project(hungarian)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-std=c++17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Boost REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories("src/")
include_directories("/opt/homebrew/Cellar/boost/1.82.0_1/include")
link_directories(/opt/homebrew/Cellar/boost/1.82.0_1/lib)


file(GLOB SRC
     "./*.cpp"
)

# Add your source files and set up the build
add_executable(hung src/main.cpp ${SRC})

# Add your test files
add_executable(test src/tests/test_hungarian.cpp)
