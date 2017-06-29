import literal_semantic
class Lsystem:
    def __init__ (self, start_literal):
        self.start = start_literal
        self.position_stack = [(0, 0, 0)]
        self.rotation_stack = [(1, 0, 0)]

    def _move(self, terminal: literal_semantic.MoveTerminal):
        self.position_stack[-1] += self.rotation_stack

    def get_vertices (self, level):
        for command in self.start.iterate(level):
            if command is literal_semantic.RotateTerminal:
                self.rotate(command)
            elif command is literal_semantic.MoveTerminal:
                self.move(command)
            elif command is literal_semantic.PushTerminal:
                self.position_stack.append(self.position_stack[-1])
                self.rotation_stack.append(self.rotation_stack[-1])
            elif command is literal_semantic.PopTerminal:
                self.position_stack.pop()
                self.rotation_stack.pop()
            else:
                raise RuntimeError


