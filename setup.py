from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules=[
    Pybind11Extension(
        "RegisterSN",
        ["RegisterSN.cpp"],
    ),
]

setup(
    name="RegisterSN",
    version="0.0.1",
    author="Denzel Bautista",
    description="Un modulo para registrar lecturas de sensores para Smart Net Solutions",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
