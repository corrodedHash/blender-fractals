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
        self.vertex_stack = [(self._bm.verts.new(self.position_stack[-1]),
                              self._bm.verts.new(self._shift_pos()))]
        self._bm.verts.index_update()
        return self

    def __exit__(self, *bla):
        self._bm.to_mesh(self._mesh)

    def _shift_pos(self):
        return (self.position_stack[-1][0], self.position_stack[-1][1] + 1,
                self.position_stack[-1][2])

    def _add_vertex(self):
        new_vertex = self._bm.verts.new(self.position_stack[-1])
        new_vertex2 = self._bm.verts.new(self._shift_pos())
        self._bm.faces.new((self.vertex_stack[-1][0], self.vertex_stack[-1][1],
                            new_vertex2, new_vertex))
        self.vertex_stack[-1] = (new_vertex, new_vertex2)
        self._bm.verts.index_update()

    def _move(self, terminal: MoveTerminal):
        rot = self.rotation_stack[-1]
        new_pos = (self.position_stack[-1][0] + rot[0] * terminal.distance,
                   self.position_stack[-1][1] + rot[1] * terminal.distance,
                   self.position_stack[-1][2] + rot[2] * terminal.distance)
        self.position_stack[-1] = new_pos
        self._add_vertex()

    def _rotate(self, terminal: RotateTerminal):
        new_x = self.rotation_stack[-1][0] * math.cos(terminal.rotation) - \
            self.rotation_stack[-1][2] * math.sin(terminal.rotation)

        new_y = self.rotation_stack[-1][1]
        new_z = self.rotation_stack[-1][0] * math.sin(terminal.rotation) + \
            self.rotation_stack[-1][2] * math.cos(terminal.rotation)
        self.rotation_stack[-1] = (new_x, new_y, new_z)

    def draw_vertices(self, level):
        max_count = self._lsystem.approx_steps(level)
        bpy.context.window_manager.progress_begin(0, 99)
        tick_count = max(max_count // 100, 1)
        ticks = 0
        count = 0
        print(max_count)
        print(tick_count)
        for command in self._lsystem.start.iterate(level):
            count += 1
            if count > tick_count:
                ticks += count // tick_count
                count = count % tick_count
                bpy.context.window_manager.progress_update(ticks)

                print('ticks: ' + str(ticks))

            if type(command) is RotateTerminal:
                self._rotate(command)
            elif type(command) is MoveTerminal:
                self._move(command)
            elif type(command) is PushTerminal:
                self.position_stack.append(self.position_stack[-1])
                self.rotation_stack.append(self.rotation_stack[-1])
                self.vertex_stack.append(self.vertex_stack[-1])
            elif type(command) is PopTerminal:
                self.position_stack.pop()
                self.rotation_stack.pop()
                self.vertex_stack.pop()
            else:
                raise RuntimeError(str(command))
        bpy.context.window_manager.progress_end()
        print("Needed ticks: " + str(ticks * tick_count + count))
        print("Expected ticks: " + str(max_count))


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


class Fractal_add_object(bpy.types.Operator,
                         bpy_extras.object_utils.AddObjectHelper):
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

    grammar_path = bpy.props.StringProperty(
            name="Grammar path",
            default=os.path.join(os.path.dirname(os.path.realpath(__file__)), "test_grammars", "dragon.txt"),
            description="The grammar for the fractal you want to draw",
            subtype='FILE_PATH',
            update=(lambda self, context: self.iteration = 2)
        )

    def execute(self, context):

        _create_fractal(self, context)

        return {'FINISHED'}
