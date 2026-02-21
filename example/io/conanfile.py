from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class Consumer(ConanFile):
    name = "chroma-io"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    requires = "chroma/0.0.1"
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
