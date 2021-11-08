cmake_minimum_required(VERSION 3.0.0)
set(LIBRARY_NAME detector)
set(LIBRARY_VERSION 1.7.3)
project(${LIBRARY_NAME})
add_definitions(-std=c++11)
option(BUILD_TEST "build test" OFF)
option(BUILD_EVAL "build evaluate" OFF)
option(USE_NPU "inference with npu" OFF)
option(USE_GPU "inference with gpu" OFF)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../)

message(STATUS ${CNN_LIBRARY})

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)
# find_package(glog REQUIRED NO_MODULE)

include_directories(${EIGEN3_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(/usr/local/include/I18RPublicBaseTypes ${ROOT_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC_FILES ${ROOT_DIR})
include(${ROOT_DIR}/cmake/find_lib_files.cmake)
list(APPEND SRC_DIR ${sub_dirs})

include(${ROOT_DIR}/cmake/find_device.cmake)
include_directories(${SRC_FILES})
find_source_file(SRC_FILES "*.h" "*.cpp" "*.c" "*.cc" "*.hpp")
add_library(${LIBRARY_NAME} SHARED ${SRC_FILES})

SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES VERSION ${LIBRARY_VERSION} SOVERSION 1)
target_link_libraries(${LIBRARY_NAME} ${OpenCV_LIBS} -ldl)

# gpu/npu
target_link_libraries(${LIBRARY_NAME} ${CNN_LIBRARY})

# glog
target_link_libraries(${LIBRARY_NAME} -lpthread -lglog)

# yaml
include(${ROOT_DIR}/cmake/find_yaml.cmake)
target_link_libraries(${LIBRARY_NAME} ${YAMLCPP_LIBRARY})

# gtest
if(BUILD_TEST)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
endif()

# evaluate
if(BUILD_EVAL)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/evaluate)
endif()

# make install
install(TARGETS ${LIBRARY_NAME}
        RUNTIME DESTINATION bin ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION lib ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION include ${CMAKE_INSTALL_INCLUDEDIR}
        ARCHIVE DESTINATION lib ${CMAKE_INSTALL_LIBDIR}
        )
set(INSTALL_HEAD_FILES ${LIBRARY_NAME}.h)
install(FILES ${INSTALL_HEAD_FILES} DESTINATION  ${CMAKE_INSTALL_PREFIX}/include)
