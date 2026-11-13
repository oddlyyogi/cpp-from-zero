cmake_minimum_required(VERSION 3.28)
project(loglens VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

add_library(loglens_core STATIC src/version.cpp src/level.cpp src/stats.cpp src/entry.cpp
            src/log_file.cpp src/ring_buffer.cpp src/sink.cpp src/kv_store.cpp)
target_sources(loglens_core PRIVATE FILE_SET CXX_MODULES FILES src/bars.cppm)
target_include_directories(loglens_core PUBLIC src)
target_compile_features(loglens_core PUBLIC cxx_std_23)
target_compile_options(loglens_core PRIVATE -Wall -Wextra -Wpedantic)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(loglens_core PRIVATE nlohmann_json::nlohmann_json)

add_executable(loglens src/main.cpp)
target_link_libraries(loglens PRIVATE loglens_core)
target_compile_options(loglens PRIVATE -Wall -Wextra -Wpedantic)
install(TARGETS loglens)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.tar.gz
    URL_HASH SHA256=6e3191c1455468b3fc35a417fb565c1c5071aee1b7e7f85e30cf48a98d37d8b5
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(loglens_tests tests/parse_test.cpp tests/store_test.cpp tests/counter_test.cpp)
target_link_libraries(loglens_tests PRIVATE loglens_core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(loglens_tests)
