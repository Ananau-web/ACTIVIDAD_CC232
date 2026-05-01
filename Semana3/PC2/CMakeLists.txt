cmake_minimum_required(VERSION 3.20)

# Cambiamos el nombre al proyecto de tu PC2
project(PC2_MergeKLists LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =====================================================================
# 1. PRIMERO: Configurar el archivo .h (Tu MergeKLists.h en include/)
# =====================================================================
# Creamos una librería "interface" (solo cabeceras)
add_library(pc2_headers INTERFACE)
target_include_directories(pc2_headers INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(pc2_headers INTERFACE cxx_std_17)

# Función auxiliar del curso para vincular dependencias fácilmente
function(cc232_link_math_if_needed target_name)
    if(UNIX AND NOT APPLE)
        target_link_libraries(${target_name} PRIVATE m)
    endif()
endfunction()

# Función adaptada para generar los ejecutables de tu PC2
function(cc232_add_pc2_target target_name source_file)
    add_executable(${target_name} "${source_file}")
    # Aquí vinculamos tu carpeta include/ a cada ejecutable automáticamente
    target_link_libraries(${target_name} PRIVATE pc2_headers)
    cc232_link_math_if_needed(${target_name})
endfunction()


# =====================================================================
# 2. EL MAIN.CPP (Pruebas principales)
# =====================================================================
cc232_add_pc2_target(test_merge "tests/main.cpp")


# =====================================================================
# 3. LUEGO: Demos y Benchmarks
# =====================================================================
cc232_add_pc2_target(demo_merge "demos/demo_merge.cpp")
cc232_add_pc2_target(bench_merge "benchmark/benchmark_merge.cpp")