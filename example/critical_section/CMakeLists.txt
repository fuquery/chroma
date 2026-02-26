cmake_minimum_required(VERSION 3.15)
project(chroma-examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(chroma REQUIRED)

add_executable(chroma-critical-section src/main.cpp)
target_link_libraries(chroma-critical-section PRIVATE chroma::chroma)
target_include_directories(chroma-critical-section PRIVATE include)

# WORKAROUND:
# Conan needs the new CMakeConfigDeps generator to handle INTERFACE options etc properly
target_compile_features(chroma-critical-section PRIVATE cxx_std_26)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(chroma-critical-section PRIVATE "-stdlib=libc++" "-freflection-latest")
  target_link_options(chroma-critical-section PRIVATE "-stdlib=libc++")
  target_link_libraries(chroma-critical-section PRIVATE "c++abi")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(chroma-critical-section PRIVATE "-freflection")
endif()
