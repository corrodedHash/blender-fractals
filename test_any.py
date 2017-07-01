import unittest
import lsystem.lsystem_parse


class TestSystem(unittest.TestCase):

    def test_general(self):
        x = None
        with open("test_grammars/a.txt") as f:
            x = lsystem.lsystem_parse.parse(f.read())

        self.assertTrue('A' in x._non_terminals)
        self.assertEqual(x.start, x._non_terminals['A'])
        self.assertEqual(x._non_terminals['A'].transition[0].distance, 2)
