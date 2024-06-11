cmake_minimum_required(VERSION 3.25)
project(MonkeyType)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)

FetchContent_MakeAvailable(fmt)

set(BUILD_SHARED_LIBS FALSE)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(SFML)

add_executable(MonkeyType main.cpp
        draw.cpp
        draw.h
        const.h
        parse.cpp
        parse.h
        setget.cpp
        setget.h)

target_link_libraries(MonkeyType sfml-graphics)
target_link_libraries(MonkeyType fmt)
