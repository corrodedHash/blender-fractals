from .util.vector import Vector
from .util.timer import Timer

from .lsystem.lsystem_class import Lsystem
from .lsystem.literal_semantic import (RotateTerminal,
                                       MoveTerminal, DrawTerminal,
                                       PushTerminal, PopTerminal)
import bpy
import math


class FractalGen:


    def __init__(self):

        self.position_stack = [Vector(0, 0, 0)]
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

    def _push(self, terminal: PushTerminal):
        for stack in self.stacks:
            stack.append(stack[-1])

    def _pop(self, terminal: PopTerminal):
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

        handler_name, handler_func = FractalGen._terminal_mapping[type(command)]

        timer = Timer()
        with timer:
            handler_func(self, command)
        self._timings[handler_name] += timer.msecs

    def _print_timings(self):
        for command in self._timings:
            print("%7s: %.4f" % (command, self._timings[command]))

    def _apply_node(self):
        profile_mesh = bpy.data.meshes.new("FractalMesh")
        profile_mesh.from_pydata(self.verts, self.edges, [])
        profile_mesh.update()

        profile_object = bpy.data.objects.new("Fractal", profile_mesh)
        profile_object.data = profile_mesh

        scene = bpy.context.scene
        scene.objects.link(profile_object)
        profile_object.select = True

    def draw_vertices(self, level, lsystem, update_callback):
        max_count = lsystem.approx_steps(level)
        tick_count = max(max_count // 100, 1)
        ticks = 0
        count = 0
        print("Expected ticks: " + str(max_count))

        with Timer("Node gen", True):
            for command in lsystem.start.iterate(level):
                count += 1
                if count > tick_count:
                    ticks += count // tick_count
                    count = count % tick_count
                    update_callback(ticks)

                self._handle_command(command)

        print("Needed ticks: " + str(ticks * tick_count + count))

        self._print_timings()

        with Timer("Node apply", True):
            self._apply_node()
