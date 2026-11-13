# C++ from Zero

Code for the **C++ from Zero** video series: one chapter at a time, in modern C++23. The running project is loglens, a log analyser that grows into a small key-value store, with CMake presets, GoogleTest tests, sanitizers, a profile-guided speed-up, a vcpkg dependency, a first C++20 module and GitHub Actions CI.

The repository root holds the finished project from the last chapter. Every chapter also has its own folder under `chapters/` with the project exactly as it stands at the end of that chapter, so you can start from any of them. Each folder builds on its own: `cd` into it and use the commands from the video.

## Requirements

- A C++23 compiler. The videos use GCC 16 (`g++`) as the main compiler and Clang/LLVM 23 for the sanitizers, `lldb` and the profile. CI also builds with GCC 14 and Clang 19.
- CMake 3.28 or newer (the videos use CMake 4.4) and Ninja.
- From chapter 13: GoogleTest 1.18.0, downloaded by CMake's FetchContent on the first configure.
- From chapter 14: vcpkg, cloned next to the project (`../vcpkg`), which installs nlohmann-json from `vcpkg.json`:

```
git clone https://github.com/microsoft/vcpkg.git ../vcpkg
../vcpkg/bootstrap-vcpkg.sh -disableMetrics      # bootstrap-vcpkg.bat on Windows
```

## Build the finished project

```
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
./build/debug/loglens logs/app.log
./build/debug/loglens logs/app.log --format json
./build/debug/loglens kv list
```

Other presets: `release`, `asan` (Clang with AddressSanitizer and UBSan), `tsan` (Clang with ThreadSanitizer) and `profile` (Clang instrumentation profile). The files in `play/` and `cpp26/` are small experiments compiled directly with `g++`, as shown in the videos; `cpp26/` needs GCC 16 (`-std=c++26 -freflection`, `-fcontracts`).

## Chapters

| # | Chapter | Folder |
|---|---------|--------|
| 01 | Set Up a Compiler, CMake and Your First Program | [chapters/01-set-up-a-compiler-cmake-and-your-first-program](chapters/01-set-up-a-compiler-cmake-and-your-first-program) |
| 02 | Types, Variables and Control Flow | [chapters/02-types-variables-and-control-flow](chapters/02-types-variables-and-control-flow) |
| 03 | Functions, References and Headers | [chapters/03-functions-references-and-headers](chapters/03-functions-references-and-headers) |
| 04 | Strings, Vectors and Arrays | [chapters/04-strings-vectors-and-arrays](chapters/04-strings-vectors-and-arrays) |
| 05 | Pointers, Memory and Ownership | [chapters/05-pointers-memory-and-ownership](chapters/05-pointers-memory-and-ownership) |
| 06 | Classes and RAII | [chapters/06-classes-and-raii](chapters/06-classes-and-raii) |
| 07 | Move Semantics and Smart Pointers | [chapters/07-move-semantics-and-smart-pointers](chapters/07-move-semantics-and-smart-pointers) |
| 08 | Inheritance and Polymorphism | [chapters/08-inheritance-and-polymorphism](chapters/08-inheritance-and-polymorphism) |
| 09 | Templates and Concepts | [chapters/09-templates-and-concepts](chapters/09-templates-and-concepts) |
| 10 | Standard Library: Containers, Algorithms and Ranges | [chapters/10-standard-library-containers-algorithms-and-ranges](chapters/10-standard-library-containers-algorithms-and-ranges) |
| 11 | Error Handling | [chapters/11-error-handling](chapters/11-error-handling) |
| 12 | Concurrency | [chapters/12-concurrency](chapters/12-concurrency) |
| 13 | Test, Debug and Profile | [chapters/13-test-debug-and-profile](chapters/13-test-debug-and-profile) |
| 14 | Package and Ship | [chapters/14-package-and-ship](chapters/14-package-and-ship) |

## License

MIT
