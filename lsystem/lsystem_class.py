from lsystem.literal_semantic import (RotateTerminal, MoveTerminal,
                                      PushTerminal, PopTerminal, NonTerminal)

import math


class Lsystem:

    def __init__(self):
        self._non_terminals = dict()
        self.start = None
        self.position_stack = [(0, 0, 0)]
        self.rotation_stack = [(1, 0, 0)]

    def get_non_terminal(self, name):
        if name in self._non_terminals:
            return self._non_terminals[name]
        else:
            self._non_terminals[name] = NonTerminal()
            return self._non_terminals[name]

    def _move(self, terminal: MoveTerminal):
        self.position_stack[-1] += self.rotation_stack * terminal.distance

    def _rotate(self, terminal: RotateTerminal):
        new_x = self.position_stack[-1][0]
        new_y = math.cos(terminal.rotation) - math.sin(terminal.rotation)
        new_z = math.sin(terminal.rotation) + math.cos(terminal.rotation)
        self.position_stack[-1] = (new_x, new_y, new_z)

    def get_vertices(self, level):
        for command in self.start.iterate(level):
            if command is RotateTerminal:
                self._rotate(command)
            elif command is MoveTerminal:
                self._move(command)
            elif command is PushTerminal:
                self.position_stack.append(self.position_stack[-1])
                self.rotation_stack.append(self.rotation_stack[-1])
            elif command is PopTerminal:
                self.position_stack.pop()
                self.rotation_stack.pop()
            else:
                raise RuntimeError
