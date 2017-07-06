class Terminal:

    def result_len(self, iteration):
        return 1


class RotateTerminal(Terminal):

    def __init__(self, rot_x=0, rot_y=0, rot_z=0):
        self.rotation = (rot_x,
                         rot_y,
                         rot_z)

    def __str__(self):
        return "r" + str(self.rotation)

    __repr__ = __str__


class MoveTerminal(Terminal):

    def __init__(self, distance=None):
        if distance is None:
            distance = 1
        self.distance = distance

    def __str__(self):
        return "m" + str(self.distance)

    __repr__ = __str__


class DrawTerminal(Terminal):

    def __init__(self, distance=None):
        if distance is None:
            distance = 1
        self.distance = distance

    def __str__(self):
        return "d" + str(self.distance)

    __repr__ = __str__


class PushTerminal(Terminal):
    pass

    def __str__(self):
        return "push"

    __repr__ = __str__


class PopTerminal(Terminal):
    pass

    def __str__(self):
        return "pop"

    __repr__ = __str__


class Define:

    def __init__(self):
        self.transition = []

    def result_len(self, iteration):
        result = 0
        for literal in self.transition:
            result += literal.result_len(iteration)
        return result

    def iterate(self, level: int):
        if level < 0:
            raise ValueError("Level cannot be below 0")

        for literal in self.transition:
            if isinstance(literal, NonTerminal):
                if level == 0:
                    continue
                for l2literal in literal.iterate(level - 1):
                    yield l2literal
            elif isinstance(literal, Define):
                for l2literal in literal.iterate(level):
                    yield l2literal
            else:
                yield literal
        return


class NonTerminal:

    def __init__(self):
        self.transition = []
        self.final_transition = []
        self.result_len_cache = dict()

    def append_trans(self, trans):
        assert trans is RotateTerminal \
            or trans is MoveTerminal \
            or trans is PushTerminal \
            or trans is PopTerminal \
            or trans is NonTerminal
        self.transition.append(trans)

    def append_final_trans(self, trans):
        assert trans is RotateTerminal \
            or trans is MoveTerminal \
            or trans is PushTerminal \
            or trans is PopTerminal
        self.final_transition.append(trans)

    def result_len(self, iteration):
        if iteration == 0 or not self.transition:
            return len(self.final_transition)
        if iteration not in self.result_len_cache:
            self.result_len_cache[iteration] = 0
            for literal in self.transition:
                self.result_len_cache[iteration] += \
                    literal.result_len(iteration - 1)
        return self.result_len_cache[iteration]

    def iterate(self, level: int):
        if level < 0:
            raise ValueError("Level cannot be below 0")

        if level == 0 or not self.transition:
            for x in self.final_transition:
                if isinstance(x, Define):
                    for y in x.iterate(level):
                        yield y
                else:
                    yield x
            return

        for literal in self.transition:
            if isinstance(literal, NonTerminal):
                for l2literal in literal.iterate(level - 1):
                    yield l2literal
            elif isinstance(literal, Define):
                for l2literal in literal.iterate(level):
                    yield l2literal
            else:
                yield literal
        return
