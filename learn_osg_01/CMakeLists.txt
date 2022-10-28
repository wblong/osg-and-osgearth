
cmake_minimum_required(VERSION 3.21)
project("learn_osg_01")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

set(OSG_DIR ${PROJECT_SOURCE_DIR}/../osgdir/installed/x64-windows)

include_directories(${OSG_DIR}/include)
link_directories(${OSG_DIR}/debug/lib)
 
add_executable(${PROJECT_NAME} main.cpp)
 
target_link_libraries(${PROJECT_NAME} 
	osgd
	osgViewerd
)

file(GLOB OSG_DLLS ${OSG_DIR}/debug/bin/*.dll)
file(COPY ${OSG_DLLS} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug)