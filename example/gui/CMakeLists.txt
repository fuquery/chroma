cmake_minimum_required(VERSION 3.15)
project(chroma-examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(chroma REQUIRED)

add_executable(chroma-gui src/main.cpp)
target_link_libraries(chroma-gui PRIVATE chroma::chroma)

# find_package(OpenGL REQUIRED)
# target_link_libraries(chroma-gui PRIVATE OpenGL::GL)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
target_link_libraries(chroma-gui PRIVATE OpenGL::GL GLUT::GLUT)


target_link_libraries(chroma-gui PRIVATE
    ${WAYLAND_CLIENT_LIB}
    ${WAYLAND_EGL_LIB}
    ${EGL_LIB}
)
target_include_directories(chroma-gui PRIVATE include)

# WORKAROUND:
# Conan needs the new CMakeConfigDeps generator to handle INTERFACE options etc properly
target_compile_features(chroma-gui PRIVATE cxx_std_26)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(chroma-gui PRIVATE "-stdlib=libc++" "-freflection-latest")
  target_link_options(chroma-gui PRIVATE "-stdlib=libc++")
  target_link_libraries(chroma-gui PRIVATE "c++abi")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(chroma-gui PRIVATE "-freflection")
endif()
