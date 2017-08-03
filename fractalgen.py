import math

from util.vector import Vector
from util.timer import Timer

from lsystem.lsystem_class import Lsystem
from lsystem.literal_semantic import (RotateTerminal,
                                      MoveTerminal, DrawTerminal,
                                      PushTerminal, PopTerminal)

try:
    import bpy
except ImportError:
    print("Could not locate blender python module, testing environment only")


class FractalGen:

    def __init__(self, level: int, lsystem: Lsystem, update_callback, start_point=(0, 0, 0)):

        self._lsystem = lsystem
        self._update_callback = update_callback
        self._level = level

        self._max_count = self._lsystem.approx_steps(level)
        self._tick_count = max(self._max_count // 100, 1)
        self._ticks = 0
        self._count = 0

        self.position_stack = [Vector(*start_point)]
        self.rotation_stack = [Vector(1, 0, 0)]
        self.degree_stack = [Vector(0, 0, 0)]
        self.verts_stack = [0]

        self.verts = [self.position_stack[-1].values]
        self.edges = []

        self.stacks = [self.position_stack,
                       self.rotation_stack,
                       self.degree_stack,
                       self.verts_stack]

        self._timings = {x: 0 for x in (
            "Rotate", "Move", "Draw", "Push", "Pop")}

    def _move(self, terminal: (MoveTerminal, DrawTerminal)):
        self.position_stack[-1] += self.rotation_stack[-1] * terminal.distance
        self.verts.append(self.position_stack[-1].values)
        self.edges.append((self.verts_stack[-1], len(self.verts) - 1))
        self.verts_stack[-1] = len(self.verts) - 1

    def _yz_rot(self):
        y = math.radians(self.degree_stack[-1][0])
        z = math.radians(self.degree_stack[-1][1])

        a = math.cos(z)
        c = math.sin(z)
        e = math.cos(y)
        g = math.sin(y)

        self.rotation_stack[-1] = Vector(e * a, e * c, g)

    def _rotate(self, terminal: RotateTerminal):
        self.degree_stack[-1] = self.degree_stack[-1] + \
            Vector(terminal.rotation[0], terminal.rotation[1], 0)
        self._yz_rot()

    def _push(self, _terminal: PushTerminal):
        for stack in self.stacks:
            stack.append(stack[-1])

    def _pop(self, _terminal: PopTerminal):
        for stack in self.stacks:
            stack.pop()

    _terminal_mapping = {RotateTerminal: ("Rotate", _rotate),
                         MoveTerminal: ("Move", _move),
                         DrawTerminal: ("Draw", _move),
                         PushTerminal: ("Push", _push),
                         PopTerminal: ("Pop", _pop)}

    def _handle_command(self, command):
        if type(command) not in FractalGen._terminal_mapping:
            raise RuntimeError(str(command))

        handler_name, handler_func = FractalGen._terminal_mapping[type(
            command)]

        timer = Timer()
        with timer:
            handler_func(self, command)
        self._timings[handler_name] += timer.msecs

    def _print_timings(self):
        for command in self._timings:
            print("%7s: %.4f" % (command, self._timings[command]))

    def _update_tick(self):
        self._count += 1
        if self._count > self._tick_count:
            self._ticks += self._count // self._tick_count
            self._count = self._count % self._tick_count
            self._update_callback(self._ticks)

    def _apply_node(self):
        profile_mesh = bpy.data.meshes.new("FractalMesh")
        profile_mesh.from_pydata(self.verts, self.edges, [])
        profile_mesh.update()

        profile_object = bpy.data.objects.new("Fractal", profile_mesh)
        profile_object.data = profile_mesh

        scene = bpy.context.scene
        scene.objects.link(profile_object)
        profile_object.select = True

    def draw_vertices(self):
        """Generates the vertices based on the given lsystem and level"""
        print("Expected ticks: " + str(self._max_count))

        with Timer("Node gen", True):
            for command in self._lsystem.start.iterate(self._level):
                self._update_tick()
                self._handle_command(command)

        print("Needed ticks: " + str(self._ticks * self._tick_count + self._count))

        self._print_timings()

        with Timer("Node apply", True):
            self._apply_node()
