import fractal_cpp.cython.fractalgen as fractalgen
import unittest

class ImportTest(unittest.TestCase):
    def test_standard(self):
        a = fractalgen.generate_fractal("examples/standard/dragon.txt", 3)
