cmake_minimum_required(VERSION 2.8)

project(Kvp)

include_directories(library)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)

file(GLOB library_headers library/Kvp/*.hpp)
file(GLOB library_sources library/Kvp/*.cpp)
add_library(kvp ${library_headers} ${library_sources})

file(GLOB test_headers test/*.hpp)
file(GLOB test_sources test/*.cpp)
add_executable(kvp-test ${test_headers} ${test_sources})
target_link_libraries(kvp-test kvp boost_unit_test_framework)

enable_testing()
add_test(kvp-test kvp-test)

