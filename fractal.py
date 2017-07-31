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

    def __call__(self, name=None, verbose=False):
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

    def _push(self):
        for stack in self.stacks:
            stack.append(stack[-1])

    def _pop(self):
        for stack in self.stacks:
            stack.pop()

    _terminal_mapping = {RotateTerminal: ("Rotate", _rotate),
                         MoveTerminal: ("Move", _move),
                         DrawTerminal: ("Draw", _move),
                         PushTerminal: ("Push", _push),
                         PopTerminal: ("Pop", _pop)}

    def _handle_command(self, command):
        timer = Timer()
        if type(command) not in self._terminal_mapping:
            raise RuntimeError(str(command))

        handler_name, handler_func = self._terminal_mapping[type(command)]
        with timer:
            handler_func(self, command)
        self._timings[handler_name] += timer.msecs

    def _apply_node(self):
        profile_mesh = bpy.data.meshes.new("FractalMesh")
        profile_mesh.from_pydata(self.verts, self.edges, [])
        profile_mesh.update()

        profile_object = bpy.data.objects.new("Fractal", profile_mesh)
        profile_object.data = profile_mesh

        scene = bpy.context.scene
        scene.objects.link(profile_object)
        profile_object.select = True

    def draw_vertices(self, level):
        max_count = self._lsystem.approx_steps(level)
        bpy.context.window_manager.progress_begin(0, 99)
        tick_count = max(max_count // 100, 1)
        ticks = 0
        count = 0
        print("Expected ticks: " + str(max_count))

        with Timer("Node gen", True):
            for command in self._lsystem.start.iterate(level):
                count += 1
                if count > tick_count:
                    ticks += count // tick_count
                    count = count % tick_count
                    bpy.context.window_manager.progress_update(ticks)

                self._handle_command(command)

        bpy.context.window_manager.progress_end()
        print("Needed ticks: " + str(ticks * tick_count + count))

        with Timer("Node apply", True):
            self._apply_node()

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
