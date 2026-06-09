# Versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.10)

project(PC3_CC232_MinXorPair)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1. Le decimos a CMake que busque en tu carpeta include general
include_directories(include)

# 2. Le decimos que también busque dentro de las subcarpetas que acabas de crear
include_directories(include/Semana5)
include_directories(include/Semana6)

# Ejecutable principal de pruebas
add_executable(test_pc3 
    tests/main.cpp 
    src/XorManager.cpp
)

# Ejecutable del demo de traza 
add_executable(demo_traza
    demos/traza_reto.cpp
    src/XorManager.cpp
)

# Soporte para ctest 
enable_testing()
add_test(NAME test_pc3 COMMAND test_pc3)