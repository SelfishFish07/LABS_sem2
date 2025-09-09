cmake_minimum_required(VERSION 3.20)
project(Tetris LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include_directories(
    /usr/include
    /usr/local/include
)

add_executable(tetris
    main.c
    tetris.c
)

target_link_libraries(tetris PRIVATE m)
target_include_directories(tetris PRIVATE .)
