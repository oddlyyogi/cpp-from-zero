cmake_minimum_required(VERSION 3.28)
project(loglens VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_library(loglens_core STATIC src/version.cpp src/level.cpp src/stats.cpp src/entry.cpp
            src/log_file.cpp src/ring_buffer.cpp)
target_include_directories(loglens_core PUBLIC src)
target_compile_features(loglens_core PUBLIC cxx_std_23)
target_compile_options(loglens_core PRIVATE -Wall -Wextra -Wpedantic)

add_executable(loglens src/main.cpp)
target_link_libraries(loglens PRIVATE loglens_core)
target_compile_options(loglens PRIVATE -Wall -Wextra -Wpedantic)
