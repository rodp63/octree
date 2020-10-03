project("octree-visualization")

cmake_minimum_required(VERSION 3.15)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)

find_package(
    Qt5 COMPONENTS
    Widgets DataVisualization 3Dcore 3Drender 3Dinput 3Dextras
    REQUIRED
)

add_executable( 
    octree-visualization
    source/main.cpp
    source/scenemodifier.cpp
)

target_link_libraries(
    octree-visualization
    Qt5::Widgets
    Qt5::DataVisualization
    Qt5::3DCore
    Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
)