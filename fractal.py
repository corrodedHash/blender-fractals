import bpy

from .lsystem.lsystem_parse import parse as lparse
from .fractalgen import FractalGen
import os


def _create_fractal(self, context):
    x = None
    if self.grammar_path == "":
        return
    try:
        with open(self.grammar_path) as f:
            x = lparse(f.read())
    except FileNotFoundError:
        self.grammar_path = self.standard_path
        return
    except RuntimeError as run_err:
        msg = ""
        for err_line in run_err.args:
            msg += err_line + "\n"
        self.report({'ERROR_INVALID_INPUT'}, msg)
        self.grammar_path = self.standard_path
        return

    bpy.context.window_manager.progress_begin(0, 99)
    FractalGen(self.iteration, x, bpy.context.window_manager.progress_update,
               bpy.context.scene.cursor_location).draw_vertices()
    bpy.context.window_manager.progress_end()


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

    standard_path = os.path.join(os.path.dirname(os.path.realpath(__file__)),
                                 "examples", "sierpinski.txt")

    def reset_iteration(self, context):
        print(context)
        self.iteration = 2

    grammar_path = bpy.props.StringProperty(
        name="Grammar path",
        default= standard_path,
        description="The grammar for the fractal you want to draw",
        subtype='FILE_PATH',
        update=reset_iteration
    )

    def execute(self, context):

        _create_fractal(self, context)

        return {'FINISHED'}
