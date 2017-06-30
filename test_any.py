import unittest
import lsystem
import sys

class TestSystem(unittest.TestCase):
    def test_general(self):
        x = None
        with open("test_grammars/a.txt") as f:
            x = lsystem.parse(f.read())

        self.assertTrue('A' in x._non_terminals)
        self.assertEqual(x.start, x._non_terminals['A'])
        self.assertEqual(x._non_terminals['A'].transition[0].distance, 1)
        print(sys.path)

