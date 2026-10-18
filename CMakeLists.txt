cmake_minimum_required(VERSION 3.14)
project(ip_filter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ip_utils STATIC ip_utils.cpp ip_utils.h)
target_include_directories(ip_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ip_filter ip_filter.cpp)
target_link_libraries(ip_filter PRIVATE ip_utils)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_ip tests/test_ip.cpp)
target_link_libraries(test_ip PRIVATE ip_utils GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_ip)