cmake_minimum_required( VERSION 3.10 )

project(global_var)

set(CMAKE_CXX_STANDARD 11)

add_executable( ${PROJECT_NAME}
                global.cpp
                )
