from lsystem.literal_semantic import NonTerminal


class Lsystem:

    def __init__(self):
        self._non_terminals = dict()
        self.start = None

    def approx_steps(self, iteration):
        return self.start.result_len(iteration)

    def get_non_terminal(self, name):
        if name in self._non_terminals:
            return self._non_terminals[name]
        else:
            self._non_terminals[name] = NonTerminal()
            return self._non_terminals[name]
