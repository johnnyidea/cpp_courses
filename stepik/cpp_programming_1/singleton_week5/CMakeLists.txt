cmake_minimum_required( VERSION 3.10 )

project(singleton)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    singleton.h
    main.cpp
    )
