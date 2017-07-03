import bpy
import bpy_extras
import bmesh

from lsystem.lsystem_class import Lsystem
from lsystem.literal_semantic import (RotateTerminal, MoveTerminal,
                                      PushTerminal, PopTerminal)
import lsystem.lsystem_parse
import math
import os


class FractalGen:

    def __init__(self, lsystem: Lsystem):
        self._lsystem = lsystem

    def __enter__(self):
        self._mesh = bpy.data.meshes.new('fractalMesh')
        self._ob = bpy.data.objects.new('Fractal', self._mesh)

        bpy.context.scene.objects.link(self._ob)
        self._bm = bmesh.new()
        self._bm.from_mesh(self._mesh)

        self.position_stack = [(0, 0, 0)]
        self.rotation_stack = [(1, 0, 0)]
        self.degree_stack = [(0, 0, 0)]
        #self.vertex_stack = [(self._bm.verts.new(self.position_stack[-1]),
        #                      self._bm.verts.new(self._shift_pos()))]
        self.vertex_stack = [self._bm.verts.new(self.position_stack[-1])]

        self.stacks = [self.position_stack,
                       self.rotation_stack,
                       self.degree_stack,
                       self.vertex_stack]
        self._bm.verts.index_update()
        return self

    def __exit__(self, *bla):
        self._bm.to_mesh(self._mesh)

    def _shift_pos(self):
        return (self.position_stack[-1][0], self.position_stack[-1][1] + 1,
                self.position_stack[-1][2])

    def _add_vertex(self):
        new_vertex = self._bm.verts.new(self.position_stack[-1])
        #new_vertex2 = self._bm.verts.new(self._shift_pos())
        #self._bm.faces.new((self.vertex_stack[-1][0], self.vertex_stack[-1][1],
        #                    new_vertex2, new_vertex))
        #self.vertex_stack[-1] = (new_vertex, new_vertex2)
        self._bm.edges.new((self.vertex_stack[-1], new_vertex))
        self.vertex_stack[-1] = new_vertex
        self._bm.verts.index_update()

    def _move(self, terminal: MoveTerminal):
        rot = self.rotation_stack[-1]
        new_pos = (self.position_stack[-1][0] + rot[0] * terminal.distance,
                   self.position_stack[-1][1] + rot[1] * terminal.distance,
                   self.position_stack[-1][2] + rot[2] * terminal.distance)
        self.position_stack[-1] = new_pos
        self._add_vertex()

    def _rotate_x(self, vector, rotation):
        new_x = vector[0]
        new_y = vector[1] * math.cos(rotation) - \
            vector[2] * math.sin(rotation)

        new_z = vector[1] * math.sin(rotation) + \
            vector[2] * math.cos(rotation)
        return (new_x, new_y, new_z)

    def _rotate_y(self, vector, rotation):
        new_x = vector[0] * math.cos(rotation) - \
            vector[2] * math.sin(rotation)

        new_y = vector[1]
        new_z = vector[0] * math.sin(rotation) + \
            vector[2] * math.cos(rotation)
        return (new_x, new_y, new_z)

    def _rotate_z(self, vector, rotation):
        new_x = vector[0] * math.cos(rotation) - \
            vector[1] * math.sin(rotation)

        new_y = vector[0] * math.sin(rotation) + \
            vector[1] * math.cos(rotation)
        new_z = vector[2]
        return (new_x, new_y, new_z)

    def _rotate(self, terminal: RotateTerminal):
        new_x = (self.degree_stack[-1][0] + terminal.rotation[0]) % 360
        new_y = (self.degree_stack[-1][1] + terminal.rotation[1]) % 360
        new_rot = (1, 0, 0)
        new_rot = self._rotate_y(new_rot, new_x * 0.0174533)
        new_rot = self._rotate_z(new_rot, new_y * 0.0174533)

        self.rotation_stack[-1] = new_rot
        self.degree_stack[-1] = (new_x, new_y, 0)

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
        for command in self._lsystem.start.iterate(level):
            print(command)
            count += 1
            if count > tick_count:
                ticks += count // tick_count
                count = count % tick_count
                bpy.context.window_manager.progress_update(ticks)

            if type(command) is RotateTerminal:
                self._rotate(command)
            elif type(command) is MoveTerminal:
                self._move(command)
            elif type(command) is PushTerminal:
                self._push()
            elif type(command) is PopTerminal:
                self._pop()
            else:
                raise RuntimeError(str(command))
        bpy.context.window_manager.progress_end()
        print("Needed ticks: " + str(ticks * tick_count + count))


def _create_fractal(self, context):
    x = None
    if self.grammar_path == "":
        return
    try:
        with open(self.grammar_path) as f:
            x = lsystem.lsystem_parse.parse(f.read())
    except FileNotFoundError:
        self.grammar_path = ""

    with FractalGen(x) as frac:
        frac.draw_vertices(self.iteration)


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
                             "test_grammars", "3d", "cube_chain.txt"),
        description="The grammar for the fractal you want to draw",
        subtype='FILE_PATH',
        update=reset_iteration
    )

    def execute(self, context):

        _create_fractal(self, context)

        return {'FINISHED'}
