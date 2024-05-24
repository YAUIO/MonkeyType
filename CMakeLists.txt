cmake_minimum_required(VERSION 3.28)
project(MonkeyType)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
set(BUILD_SHARED_LIBS FALSE)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)

FetchContent_MakeAvailable(fmt)

FETCHCONTENT_DECLARE(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.1
)

FETCHCONTENT_MAKEAVAILABLE(SFML)

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
