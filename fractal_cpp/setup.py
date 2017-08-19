"""Setup for the c part of this addon"""

from distutils.core import setup
from distutils.extension import Extension

from Cython.Build import cythonize


def bla():
    """Build the stuff"""
    my_ex = Extension(name="fractal",
                      sources=["literal.cpp", "lgrammarVisitor.cpp", "fractal.pyx"],
                      extra_compile_args=['-std=c++11', "-Iparsing/antlr-runtime/runtime/src/"],
                      extra_objects=["parsing/antlr4.a", "parsing/parser.a"],
                      language="c++")
    setup(
        ext_modules=cythonize(my_ex)
    )


bla()
