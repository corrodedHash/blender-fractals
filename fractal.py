import bpy

from .lsystem.lsystem_class import Lsystem
from .lsystem.literal_semantic import (RotateTerminal,
                                       MoveTerminal, DrawTerminal,
                                       PushTerminal, PopTerminal)

from .vector import Vector

from .lsystem.lsystem_parse import parse as lparse
import os
import time
import math


class Timer(object):
    def __init__(self, name=None, verbose=False):
        self.verbose = verbose
        self.name = name

    def __enter__(self):
        self.start = time.time()
        return self

    def __exit__(self, *args):
        self.end = time.time()
        self.secs = self.end - self.start
        self.msecs = self.secs * 1000  # millisecs
        if self.verbose:
            print('%s elapsed time: %f ms' % (self.name, self.msecs))


class CommandTimer(object):
    timing_dict = dict()

    def __init__(self, name=None, verbose=False):
        self.verbose = verbose
        self.name = name

    def __enter__(self):
        self.start = time.time()
        return self

    def __exit__(self, *args):
        self.end = time.time()
        self.secs = self.end - self.start
        self.msecs = self.secs * 1000  # millisecs
        if self.verbose:
            print('%s elapsed time: %f ms' % (self.name, self.msecs))
        if self.name not in self.timing_dict:
            self.timing_dict[self.name] = []
        self.timing_dict[self.name].append(self.msecs)

    @classmethod
    def reset(cls):
        cls.timing_dict = dict()

    @classmethod
    def get_timings(cls):
        for x in cls.timing_dict:
            print("%s: %0.4f %5d" % (x.ljust(10), sum(cls.timing_dict[x]) /
                                     len(cls.timing_dict[x]),
                                     len(cls.timing_dict[x])))


class FractalGen:

    def __init__(self, lsystem: Lsystem):
        self._lsystem = lsystem

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

    def _push(self):
        for stack in self.stacks:
            stack.append(stack[-1])

    def _pop(self):
        for stack in self.stacks:
            stack.pop()

    def draw_vertices(self, level):
        max_count = self._lsystem.approx_steps(level)
        bpy.context.window_manager.progress_begin(0, 99)
        tick_count = max(max_count // 100, 1)
        ticks = 0
        count = 0
        print("Expected ticks: " + str(max_count))

        CommandTimer.reset()
        with Timer("Node gen", True):
            for command in self._lsystem.start.iterate(level):
                count += 1
                if count > tick_count:
                    ticks += count // tick_count
                    count = count % tick_count
                    bpy.context.window_manager.progress_update(ticks)

                if type(command) is RotateTerminal:
                    with CommandTimer("Rotate"):
                        self._rotate(command)
                elif type(command) is MoveTerminal:
                    with CommandTimer("Move"):
                        self._move(command)
                elif type(command) is DrawTerminal:
                    with CommandTimer("Draw"):
                        self._move(command)
                elif type(command) is PushTerminal:
                    with CommandTimer("Push"):
                        self._push()
                elif type(command) is PopTerminal:
                    with CommandTimer("Pop"):
                        self._pop()
                else:
                    raise RuntimeError(str(command))
        bpy.context.window_manager.progress_end()
        print("Needed ticks: " + str(ticks * tick_count + count))
        with Timer("Node apply", True):
            profile_mesh = bpy.data.meshes.new("FractalMesh")
            profile_mesh.from_pydata(self.verts, self.edges, [])
            profile_mesh.update()

            profile_object = bpy.data.objects.new("Fractal", profile_mesh)
            profile_object.data = profile_mesh

            scene = bpy.context.scene
            scene.objects.link(profile_object)
            profile_object.select = True

        CommandTimer.get_timings()


def _create_fractal(self, context):
    x = None
    if self.grammar_path == "":
        return
    try:
        with open(self.grammar_path) as f:
            x = lparse(f.read())
    except FileNotFoundError:
        self.grammar_path = ""
        return

    FractalGen(x).draw_vertices(self.iteration)


class Fractal_add_object(bpy.types.Operator):
    """Create a new Fractal"""
    bl_idname = "mesh.add_fractal"
    bl_label = "Add Fracal"
    bl_options = {'REGISTER', 'UNDO'}

    iteration = bpy.props.IntProperty(
        name="Iteration Count",
        default=2,
        min=1,
        soft_min=1,
        soft_max=7,
        subtype='UNSIGNED',
        description="Number of iterations of the fractal")

    def reset_iteration(self, context):
        self.iteration = 2
    grammar_path = bpy.props.StringProperty(
        name="Grammar path",
        default=os.path.join(os.path.dirname(os.path.realpath(__file__)),
                             "examples", "sierpinski.txt"),
        description="The grammar for the fractal you want to draw",
        subtype='FILE_PATH',
        update=reset_iteration
    )

    def execute(self, context):

        _create_fractal(self, context)

        return {'FINISHED'}
