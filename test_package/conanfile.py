import os
from conan import ConanFile
from conan.tools.build import can_run


class udp_chatTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def test(self):
        if can_run(self):
            self.run("udp-chat", env="conanrun")
