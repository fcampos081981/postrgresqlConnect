cmake_minimum_required(VERSION 3.20)
project(postrgresqlConnect)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

add_executable(postrgresqlConnect main.cpp
        FilesFunctions.cpp
        FilesFunctions.h
        DatabaseFunctions.cpp
        DatabaseFunctions.h
        DataGenerator.cpp
        DataGenerator.h
        EnvLoader.cpp
        EnvLoader.h)
target_include_directories(postrgresqlConnect PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(postrgresqlConnect PRIVATE ${PQXX_LIBRARIES})