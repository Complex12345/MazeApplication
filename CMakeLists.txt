cmake_minimum_required(VERSION 3.21)
project(MyQtCudaProject LANGUAGES CXX CUDA)

# Compiler and language settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Qt setup
# Adjust the path if Qt is installed in a different location
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.3/msvc2022_64/lib/cmake/Qt6")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# CUDA setup
find_package(CUDAToolkit QUIET)
if (CUDAToolkit_FOUND)
    message(STATUS "CUDA Toolkit found at: ${CUDAToolkit_LIBRARY_DIR}")
else()
    message(WARNING "CUDA Toolkit not found. Building without GPU acceleration.")
endif()

# Source files
add_executable(MyQtCudaProject
        src/main.cpp
        src/gui/MainWindow.cpp
        src/Maze.cpp
        src/gui/MazeConfigurationGui.cpp
        src/SystemInfo.cpp
        src/gui/MazeWidget.cpp
        src/maze_generation_cpu/DfsGeneratorCpu.cpp
        src/maze_solver_cpu/Bfs.cpp
        include/cuda/kernel.cu
        include/MainWindow.h
        include/Maze.h
        include/MazeConfigurationGui.h
        include/MazeGenerator.h
        include/MazeWidget.h
)

# Linking and include directories
target_link_libraries(MyQtCudaProject PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(MyQtCudaProject PRIVATE ${CMAKE_SOURCE_DIR}/include)

if (CUDAToolkit_FOUND)
    target_include_directories(MyQtCudaProject PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
    target_link_libraries(MyQtCudaProject PRIVATE CUDA::cudart)
    target_compile_definitions(MyQtCudaProject PRIVATE USE_CUDA)
endif()

# Post-build steps for Windows: deploy Qt and copy CUDA DLLs
if (WIN32)
    # Path to windeployqt (Qt deployment tool)
    set(QT_DEPLOY_TOOL "C:/Qt/6.9.3/msvc2022_64/bin/windeployqt.exe")

    # Path to CUDA runtime DLL
    set(CUDA_DLL_PATH "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.0/bin/x64/cudart64_13.dll")

    # Run windeployqt after build
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(QT_DEPLOY_MODE "--debug")
    else()
        set(QT_DEPLOY_MODE "--release")
    endif()

    add_custom_command(TARGET MyQtCudaProject POST_BUILD
            COMMAND "${QT_DEPLOY_TOOL}" ${QT_DEPLOY_MODE} "$<TARGET_FILE:MyQtCudaProject>"
            COMMENT "Running windeployqt to deploy Qt runtime files..."
    )

    # Copy CUDA runtime DLL to the build output folder
    if (EXISTS "${CUDA_DLL_PATH}")
        add_custom_command(TARGET MyQtCudaProject POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CUDA_DLL_PATH}"
                "$<TARGET_FILE_DIR:MyQtCudaProject>"
                COMMENT "Copying CUDA runtime DLL..."
        )
    else()
        message(WARNING "CUDA runtime DLL not found at ${CUDA_DLL_PATH}")
    endif()
endif()

# Output directories
set_target_properties(MyQtCudaProject PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>
)

# Summary message
message(STATUS "-----------------------------------------------------")
message(STATUS "Project: MyQtCudaProject")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output: ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
message(STATUS "Qt found: ${Qt6_DIR}")
if (CUDAToolkit_FOUND)
    message(STATUS "CUDA support: ENABLED")
else()
    message(STATUS "CUDA support: DISABLED")
endif()
message(STATUS "-----------------------------------------------------")
