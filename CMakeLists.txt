cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

# set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(chroma VERSION 0.1 LANGUAGES CXX)
include(GNUInstallDirs)
add_library(chroma INTERFACE)

# temporary compiler-specific flags to enable reflection
target_compile_features(chroma INTERFACE cxx_std_26)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(chroma INTERFACE "-stdlib=libc++" "-freflection-latest")
  target_link_options(chroma INTERFACE "-stdlib=libc++")
  target_link_libraries(chroma INTERFACE "c++abi")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(chroma INTERFACE "-freflection")
endif()


target_include_directories(chroma INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

install(TARGETS chroma EXPORT chroma-targets)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT chroma-targets
    FILE chroma-targets.cmake
    DESTINATION lib/cmake/chroma
)