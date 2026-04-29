cmake_minimum_required(VERSION 3.20)

project(PC2_MergeKLists LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(pc2_headers INTERFACE)
target_include_directories(pc2_headers INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(pc2_headers INTERFACE cxx_std_17)

function(cc232_link_math_if_needed target_name)
    if(UNIX AND NOT APPLE)
        target_link_libraries(${target_name} PRIVATE m)
    endif()
endfunction()

function(cc232_add_pc2_target target_name source_file)
    add_executable(${target_name} "${source_file}")
    target_link_libraries(${target_name} PRIVATE pc2_headers)
    cc232_link_math_if_needed(${target_name})
endfunction()

# 2. EL MAIN.CPP (Pruebas principales)
cc232_add_pc2_target(test_merge "tests/main.cpp")