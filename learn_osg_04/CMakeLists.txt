cmake_minimum_required(VERSION 3.21)
project("learn_osg_04")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(OSG_DIR ${PROJECT_SOURCE_DIR}/../osgdir/installed/x64-windows)
include_directories(${OSG_DIR}/include)
link_directories(${OSG_DIR}/debug/lib)

add_executable (${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
    osgd
	osgDBd
	osgViewerd
)
file(GLOB OSG_DLLS ${OSG_DIR}/debug/bin/*.dll)
file(COPY ${OSG_DLLS} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug)

file(GLOB OSG_PLUGIN_DLLS ${OSG_DIR}/debug/tools/osg/osgPlugins-3.6.5/*.dll)
file(COPY ${OSG_PLUGIN_DLLS} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug)