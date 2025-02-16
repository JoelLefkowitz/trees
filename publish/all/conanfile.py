import os

from conan import ConanFile
from conan.tools.files import copy, get
from conan.tools.layout import basic_layout


class TreesConan(ConanFile):
    name = "trees"
    description = "Extensible tree data structure."
    license = "MIT"

    url = "https://github.com/conan-io/conan-center-index"
    homepage = "https://github.com/JoelLefkowitz/trees"

    topics = (
        "tree",
        "graph",
        "degrees",
        "node",
        "header-only",
    )

    package_type = "header-library"
    settings = (
        "os",
        "arch",
        "compiler",
        "build_type",
    )

    no_copy_source = True

    requires = ("funky/0.1.0",)

    def layout(self):
        basic_layout(self, src_folder="src")

    def package_id(self):
        self.info.clear()

    def source(self):
        get(self, **self.conan_data["sources"][self.version], strip_root=True)

    def build(self):
        pass

    def package(self):
        copy(
            self,
            "LICENSE.md",
            self.source_folder,
            os.path.join(self.package_folder, "licenses"),
        )
        copy(
            self,
            "*.[ht]pp",
            os.path.join(self.source_folder, "src"),
            os.path.join(self.package_folder, "include", self.name),
        )

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
