from conan import ConanFile
from conan.tools.files import copy
import os

class MyLibConan(ConanFile):
    name = "chroma"
    version = "0.0.1"
    package_type = "header-library"
    exports_sources = "include/*", "CMakeLists.txt"
    no_copy_source = True

    def package(self):
        copy(self, "*", self.source_folder, os.path.join(self.package_folder, "include"))

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []