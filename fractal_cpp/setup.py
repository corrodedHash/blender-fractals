"""Setup for the c part of this addon"""

from distutils.core import setup
from distutils.extension import Extension

from Cython.Build import cythonize


def bla():
    """Build the stuff"""
    my_ex = Extension(name="fractal",
                      sources=["fractalgen.cpp", "literal.cpp", "fractal.pyx", "array_wrapper.pyx"],
                      extra_compile_args=[
                          '-std=c++14', "-Iparsing/antlr-runtime/runtime/src/"],
                      extra_link_args=["-std=c++11"],
                      extra_objects=["parsing/parser.a", "parsing/antlr4.a"],
                      language="c++")
    setup(
        ext_modules=cythonize(my_ex)
    )


bla()
