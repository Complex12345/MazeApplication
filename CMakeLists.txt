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

find_package(CUDAToolkit QUIET)

add_executable(MyQtCudaProject
        src/main.cpp
        src/gui/MainWindow.cpp
        src/Maze.cpp
        src/gui/MazeConfigurationGui.cpp
        src/SystemInfo.cpp
        include/MainWindow.h
        include/Maze.h
        include/MazeConfigurationGui.h
        include/cuda/kernel.cu
        include/MazeGenerator.h
        include/MazeWidget.h
        src/gui/MazeWidget.cpp
)

add_executable(testCpuName
        test/testSystemInfo.cpp
        src/SystemInfo.cpp
)

add_executable(testMaze
        test/MazeTest.cpp
        include/Maze.h
        src/Maze.cpp
        include/MazeGenerator.h
        src/maze/MazeGenerator.cpp
        src/maze_cpu/DfsGeneratorCpu.cpp
)

target_link_libraries(MyQtCudaProject PRIVATE Qt6::Core Qt6::Widgets)

target_include_directories(MyQtCudaProject PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(testCpuName      PRIVATE ${CMAKE_SOURCE_DIR}/include)

if (CUDAToolkit_FOUND)
    target_include_directories(MyQtCudaProject PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
    target_include_directories(testCpuName      PRIVATE ${CUDAToolkit_INCLUDE_DIRS})

    target_link_libraries(MyQtCudaProject PRIVATE CUDA::cudart)
    target_link_libraries(testCpuName      PRIVATE CUDA::cudart)

    target_compile_definitions(testCpuName PRIVATE USE_CUDA)

else()
    message(WARNING "CUDAToolkit not found. CUDA-dependent code will not link.")
endif()
