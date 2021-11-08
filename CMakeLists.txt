cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME detector_sample)
project(${PROJECT_NAME} VERSION 1.1.3)
add_definitions(-std=c++11)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/)
file(GLOB file ${ROOT_DIR}/sample/utils/*)
add_executable(${PROJECT_NAME} sample/main.cpp ${file})

set(DETECTOR_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)
add_subdirectory(src ${DETECTOR_DIR})
add_dependencies(${PROJECT_NAME} detector)

# glog
target_link_libraries(${PROJECT_NAME} -lpthread -lglog)

# opencv
find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# eigen
find_package(Eigen3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIRS})

# npu/gpu
include(${ROOT_DIR}/cmake/find_device.cmake)
target_link_libraries(${PROJECT_NAME}  ${CNN_LIBRARY})

# yaml-cpp
include(${ROOT_DIR}/cmake/find_yaml.cmake)
target_link_libraries(${PROJECT_NAME} ${YAMLCPP_LIBRARY})

# deep learning modules
include_directories(/usr/local/include/I18RPublicBaseTypes)
include_directories(${ROOT_DIR}/src)
message(STATUS "build on processor: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
set(detector ${DETECTOR_DIR}/libdetector.so)
target_link_libraries(${PROJECT_NAME} ${detector} -ldl)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS -Wl,--no-as-needed)

execute_process(COMMAND cp -r ${ROOT_DIR}/data ${CMAKE_BINARY_DIR})

# generate readme of sample for API
set(API_DIR ${CMAKE_BINARY_DIR}/API)
execute_process(COMMAND bash ${ROOT_DIR}/scripts/gen_sample_readme.sh ${API_DIR})

# make install
install(DIRECTORY config DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY sample DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${API_DIR}/README.md DESTINATION ${CMAKE_INSTALL_PREFIX})