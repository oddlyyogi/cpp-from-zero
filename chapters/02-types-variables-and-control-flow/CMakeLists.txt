cmake_minimum_required(VERSION 3.28)
project(loglens VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_executable(loglens src/main.cpp src/version.cpp)
target_compile_features(loglens PRIVATE cxx_std_23)
target_compile_options(loglens PRIVATE -Wall -Wextra -Wpedantic)