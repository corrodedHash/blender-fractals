import literal_semantic
import math

class Lsystem:
    def __init__ (self, start_literal):
        self._non_terminals = []
        self.start = start_literal
        self.position_stack = [(0, 0, 0)]
        self.rotation_stack = [(1, 0, 0)]

    def get_non_terminal(self, name):
        if name in self._non_terminals:
            return self._non_terminals[name]
        else:
            self._non_terminals[name] = literal_semantic.NonTerminal()
            return self._non_terminals[name]


    def _move(self, terminal: literal_semantic.MoveTerminal):
        self.position_stack[-1] += self.rotation_stack * terminal.distance
    
    def _rotate(self, terminal: literal_semantic.RotateTerminal):
        new_x = self.position_stack[-1][0]
        new_y = math.cos(terminal.rotation) - math.sin(teriminal.rotation)
        new_z = math.sin(terminal.rotation) + math.cos(teriminal.rotation)
        self.position_stack[-1] = (new_x, new_y, new_z)

    def get_vertices (self, level):
        for command in self.start.iterate(level):
            if command is literal_semantic.RotateTerminal:
                self._rotate(command)
            elif command is literal_semantic.MoveTerminal:
                self._move(command)
            elif command is literal_semantic.PushTerminal:
                self.position_stack.append(self.position_stack[-1])
                self.rotation_stack.append(self.rotation_stack[-1])
            elif command is literal_semantic.PopTerminal:
                self.position_stack.pop()
                self.rotation_stack.pop()
            else:
                raise RuntimeError


