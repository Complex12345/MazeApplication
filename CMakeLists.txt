cmake_minimum_required(VERSION 3.21)
project(MyQtCudaProject LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.2/msvc2022_64/lib/cmake/Qt6")
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

find_package(CUDA REQUIRED)

add_executable(MyQtCudaProject
        src/main.cpp
        include/cuda/kernel.cu
        src/gui/MainWindow.cpp
        include/MainWindow.h
)

target_link_libraries(MyQtCudaProject PRIVATE Qt6::Core Qt6::Widgets)

set_target_properties(MyQtCudaProject PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
)

target_include_directories(MyQtCudaProject PRIVATE
        ${CMAKE_PREFIX_PATH}/../../include
)
