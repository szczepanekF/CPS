import os
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy
from conan import ConanFile

class ImGuiExample(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"


    def requirements(self):
        self.requires("imgui/1.90")
        self.requires("glfw/3.4")
        self.requires("glew/2.2.0")
        self.requires("implot/0.16")

    def generate(self):

        copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder,
                                          "res", "bindings"), os.path.join(self.source_folder, "src", "bindings"))
        # copy(self, "*glfw*.cpp", os.path.join(self.dependencies["imgui"].package_folder,
        #                                     "res", "bindings"), os.path.join(self.dependencies["imgui"].package_folder, "res", "src"))

        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
                                             "res", "bindings"), os.path.join(self.source_folder, "src", "bindings"))
        # copy(self, "*opengl3*.cpp", os.path.join(self.dependencies["imgui"].package_folder,
        #                                      "res", "bindings"), os.path.join(self.dependencies["imgui"].package_folder, "res", "src"))
        self.output.warning(self.dependencies["imgui"].package_folder)
        self.output.warning(self.source_folder)




